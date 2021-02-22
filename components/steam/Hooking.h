/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#pragma once

#include <stdint.h>

#include <memory>
#include <functional>

namespace hook
{
	// for link /DYNAMICBASE executables
	static ptrdiff_t baseAddressDifference;

	// sets the base address difference based on an obtained pointer
	inline void set_base(uintptr_t address)
	{
#ifdef _M_IX86
		uintptr_t addressDiff = (address - 0x400000);
#elif defined(_M_AMD64)
		uintptr_t addressDiff = (address - 0x140000000);
#endif

		// pointer-style cast to ensure unsigned overflow ends up copied directly into a signed value
		baseAddressDifference = *(ptrdiff_t*)&addressDiff;
	}

	// sets the base to the process main base
	inline void set_base()
	{
		set_base((uintptr_t)GetModuleHandle(NULL));
	}

	// adjusts the address passed to the base as set above
	template<typename T>
	inline void adjust_base(T& address)
	{
		*(uintptr_t*)&address += baseAddressDifference;
	}

	// returns the adjusted address to the stated base
	template<typename T>
	inline uintptr_t get_adjusted(T address)
	{
		return (uintptr_t)address + baseAddressDifference;
	}

	struct pass
	{
		template<typename ...T> pass(T...) {}
	};

	template<typename ValueType, typename AddressType>
	inline void put(AddressType address, ValueType value)
	{
		adjust_base(address);

		memcpy((void*)address, &value, sizeof(value));
	}

	template<typename ValueType, typename AddressType>
	inline void putVP(AddressType address, ValueType value)
	{
		adjust_base(address);

		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template<typename AddressType>
	inline void nop(AddressType address, size_t length)
	{
		adjust_base(address);

		memset((void*)address, 0x90, length);
	}

	template<typename AddressType>
	inline void return_function(AddressType address, uint16_t stackSize = 0)
	{
		if (stackSize == 0)
		{
			put<uint8_t>(address, 0xC3);
		}
		else
		{
			put<uint8_t>(address, 0xC2);
			put<uint16_t>((uintptr_t)address + 1, stackSize);
		}
	}

	template<typename T>
	inline T* getRVA(uintptr_t rva)
	{
#ifdef _M_IX86
		return (T*)(baseAddressDifference + 0x400000 + rva);
#elif defined(_M_AMD64)
		return (T*)(0x140000000 + rva);
#endif
	}

	namespace
	{
		template<typename TOrdinal>
		inline bool iat_matches_ordinal(uintptr_t* nameTableEntry, TOrdinal ordinal)
		{

		}

		template<>
		inline bool iat_matches_ordinal(uintptr_t* nameTableEntry, int ordinal)
		{
			if (IMAGE_SNAP_BY_ORDINAL(*nameTableEntry))
			{
				return IMAGE_ORDINAL(*nameTableEntry) == ordinal;
			}

			return false;
		}

		template<>
		inline bool iat_matches_ordinal(uintptr_t* nameTableEntry, const char* ordinal)
		{
			if (!IMAGE_SNAP_BY_ORDINAL(*nameTableEntry))
			{
				auto import = getRVA<IMAGE_IMPORT_BY_NAME>(*nameTableEntry);

				return !_stricmp((char*)import->Name, ordinal);
			}

			return false;
		}
	}

	template<typename T, typename TOrdinal>
	void iat(const char* moduleName, T function, TOrdinal ordinal)
	{
#ifdef _M_IX86
		IMAGE_DOS_HEADER* imageHeader = (IMAGE_DOS_HEADER*)(baseAddressDifference + 0x400000);
#elif defined(_M_AMD64)
		IMAGE_DOS_HEADER* imageHeader = (IMAGE_DOS_HEADER*)(baseAddressDifference + 0x140000000);
#endif
		IMAGE_NT_HEADERS* ntHeader = getRVA<IMAGE_NT_HEADERS>(imageHeader->e_lfanew);

		IMAGE_IMPORT_DESCRIPTOR* descriptor = getRVA<IMAGE_IMPORT_DESCRIPTOR>(ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

		while (descriptor->Name)
		{
			const char* name = getRVA<char>(descriptor->Name);

			if (_stricmp(name, moduleName))
			{
				descriptor++;

				continue;
			}

			auto nameTableEntry = getRVA<uintptr_t>(descriptor->OriginalFirstThunk);
			auto addressTableEntry = getRVA<uintptr_t>(descriptor->FirstThunk);

			while (*nameTableEntry)
			{
				if (iat_matches_ordinal(nameTableEntry, ordinal))
				{
					*addressTableEntry = (uintptr_t)function;
					return;
				}

				nameTableEntry++;
				addressTableEntry++;
			}

			return;
		}
	}


#define DEFINE_INJECT_HOOK(hookName, hookAddress) class _zz_inject_hook_##hookName : public hook::inject_hook { public: _zz_inject_hook_##hookName(uint32_t address) : hook::inject_hook(address) {}; ReturnType run(); }; \
	static _zz_inject_hook_##hookName hookName(hookAddress); \
	_zz_inject_hook_##hookName::ReturnType _zz_inject_hook_##hookName::run()

	template<typename T, typename AT>
	inline void jump(AT address, T func)
	{
		put<uint8_t>(address, 0xE9);
		put<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)get_adjusted(address) - 5);
	}

	template<typename T, typename AT>
	inline void call(AT address, T func)
	{
		put<uint8_t>(address, 0xE8);
		put<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)get_adjusted(address) - 5);
	}

	template<typename T>
	inline T get_call(T address)
	{
		intptr_t target = *(uintptr_t*)(get_adjusted(address) + 1);
		target += (get_adjusted(address) + 5);

		return (T)target;
	}

	template<typename TTarget, typename T>
	inline void set_call(TTarget* target, T address)
	{
		*(T*)target = get_call(address);
	}

	namespace vp
	{
		template<typename T, typename AT>
		inline void jump(AT address, T func)
		{
			putVP<uint8_t>(address, 0xE9);
			putVP<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)get_adjusted(address) - 5);
		}

		template<typename T, typename AT>
		inline void call(AT address, T func)
		{
			putVP<uint8_t>(address, 0xE8);
			putVP<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)get_adjusted(address) - 5);
		}
	}

}
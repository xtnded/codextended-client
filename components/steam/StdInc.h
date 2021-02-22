
// client-side shared include file
#if defined(_MSC_VER)
#pragma warning(disable: 4251) // needs to have dll-interface to be used by clients
#pragma warning(disable: 4273) // inconsistent dll linkage
#pragma warning(disable: 4275) // non dll-interface class used as base
#pragma warning(disable: 4244) // possible loss of data
#pragma warning(disable: 4800) // forcing value to bool
#pragma warning(disable: 4290) // C++ exception specification ignored

// MSVC odd defines
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C/C++ headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef NDEBUG
#undef NDEBUG
#include <assert.h>
#define NDEBUG
#else
#include <assert.h>
#endif

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <atomic>
#include <locale>
#include <codecvt>
#include <thread>


#define DECLARE_INSTANCE_TYPE(name) \
	template<> __declspec(selectany) const char* ::Instance<name>::ms_name = #name; \
	template<> __declspec(selectany) name* ::Instance<name>::ms_cachedInstance = nullptr;
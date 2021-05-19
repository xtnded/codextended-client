#include "stdafx.h"

void codextended();
void codextended_unload();

HMODULE hModule;
HANDLE hLogFile = INVALID_HANDLE_VALUE;

// PROCESS_DETACH is not called so don't make global declarations which have deconstructors which have to be called.
static BYTE originalCode[5];
static PBYTE originalEP = 0;
void Main_UnprotectModule(HMODULE hModule);
void Main_DoInit()
{
	// unprotect our entire PE image
	HMODULE hModule;
	if (SUCCEEDED(GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)Main_DoInit, &hModule)))
	{
		Main_UnprotectModule(hModule);
	}

	void patch_opcode_loadlibrary(void);

	// return to the original EP
	memcpy(originalEP, &originalCode, sizeof(originalCode));
	__asm jmp originalEP
}
void Main_SetSafeInit()
{
	// find the entry point for the executable process, set page access, and replace the EP
	HMODULE hModule = GetModuleHandle(NULL); // passing NULL should be safe even with the loader lock being held (according to ReactOS ldr.c)

	if (hModule)
	{
		PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hModule + header->e_lfanew);

		Main_UnprotectModule(hModule);

		// back up original code
		PBYTE ep = (PBYTE)((DWORD)hModule + ntHeader->OptionalHeader.AddressOfEntryPoint);
		memcpy(originalCode, ep, sizeof(originalCode));

		// patch to call our EP
		int newEP = (int)Main_DoInit - ((int)ep + 5);
		ep[0] = 0xE9; // for some reason this doesn't work properly when run under the debugger
		memcpy(&ep[1], &newEP, 4);

		originalEP = ep;
	}
}

#ifndef PROJECT_EXE
BOOL APIENTRY DllMain(HMODULE hMod, DWORD ul_reason_for_call, LPVOID lpReserved)
{
#if 0

	if (strstr(szModuleName, "rundll32") != NULL) {
		return TRUE;
	}
#endif

	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			char szModuleName[MAX_PATH + 1];

			GetModuleFileNameA(NULL, szModuleName, MAX_PATH);
			void MSS32_Hook();
			MSS32_Hook();

			extern bool miles32_loaded;
			if (!miles32_loaded)
				return FALSE;
			Main_SetSafeInit();
			codextended();
		break;
		case DLL_PROCESS_DETACH:
			// codextended_unload();
		break;
	}
	return TRUE;
}
#endif

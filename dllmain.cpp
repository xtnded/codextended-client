#include "stdafx.h"

void codextended();
void codextended_unload();

HMODULE hModule;
HANDLE hLogFile = INVALID_HANDLE_VALUE;

// PROCESS_DETACH is not called so don't make global declarations which have deconstructors which have to be called.

#ifndef PROJECT_EXE
BOOL APIENTRY DllMain(HMODULE hMod, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	char szModuleName[MAX_PATH + 1];

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	if (strstr(szModuleName, "rundll32") != NULL) {
		return TRUE;
	}

	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			// _chdir("C:\\Games\\Call of Duty"); // Fix for Discord RPC "Join", it shouldn't be hardcoded though.
			DisableThreadLibraryCalls(hMod);
			hModule = hMod;
			codextended();
		break;
		case DLL_PROCESS_DETACH:
			// codextended_unload();
		break;
	}
	return TRUE;
}
#endif
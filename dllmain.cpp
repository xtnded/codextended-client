#include "stdafx.h"

void codextended();
void codextended_unload();

HMODULE hModule;
#if 1
HANDLE hLogFile = INVALID_HANDLE_VALUE;
#endif

/* PROCESS_DETACH is not called so don't make global declarations which have deconstructors which have to be called.
*/

#ifndef PROJECT_EXE

BOOL APIENTRY DllMain( HMODULE hMod,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	char szModuleName[MAX_PATH + 1];

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	if (strstr(szModuleName, "rundll32") != NULL) {
		return TRUE;
	}

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH: {
			DisableThreadLibraryCalls(hMod);
			hModule = hMod;
	#if 0
	#ifdef DEBUG
			if (hLogFile == INVALID_HANDLE_VALUE) {
				hLogFile = CreateFile("./cod_mem_log.txt", GENERIC_WRITE,
					FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL, NULL);
				_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
				_CrtSetReportFile(_CRT_WARN, hLogFile);
			}
	#endif
	#endif
			
			codextended();
		}
								 break;
		case DLL_PROCESS_DETACH: {
			//codextended_unload();
		} break;
	}
	return TRUE;
}

#endif
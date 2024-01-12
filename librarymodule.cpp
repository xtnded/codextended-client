#include "shared.h"
#include "gl/gl.h"

#pragma comment(lib, "libs/detours/detours.lib")
#include "libs/detours/detours.h"

__int64 FileSize(std::string name)
{
	WIN32_FILE_ATTRIBUTE_DATA fad;
	if (!GetFileAttributesEx(name.c_str(), GetFileExInfoStandard, &fad))
		return -1; // error condition, could call GetLastError to find out more
	LARGE_INTEGER size;
	size.HighPart = fad.nFileSizeHigh;
	size.LowPart = fad.nFileSizeLow;
	return size.QuadPart;
}

HMODULE(WINAPI *orig_LoadLibraryA)(LPCSTR lpFileName);
HMODULE WINAPI hLoadLibraryA(LPSTR lpFileName) {
	if (strstr(lpFileName, "codextended"))
		return NULL;

	HMODULE hModule = orig_LoadLibraryA(lpFileName);
	DWORD pBase = (DWORD)GetModuleHandle(lpFileName);

	if (!pBase)
		return hModule;

	void Main_UnprotectModule(HMODULE hModule);
		Main_UnprotectModule(hModule);

	if (strstr(lpFileName, "ui_mp") || strstr(lpFileName, "userinterface")) { /* clients updated by server */
		if(codversion != COD_1)
			return hModule;
		if (strstr(lpFileName, "ui_mp") && FileSize(lpFileName) < 0x249F0) //150kb
			return hModule;

		void UI_Init(DWORD);
		UI_Init(pBase);

	}
	else if (strstr(lpFileName, "cgame_mp") != NULL) {
		if (codversion != COD_1)
			return hModule;
		void CG_Init(DWORD);
		CG_Init(pBase);
	}
	else if (strstr(lpFileName, "game_mp") && !strstr(lpFileName, "cgame")) {
		void G_Init(DWORD);
		G_Init(pBase);
	}

	return hModule;
}

void patch_opcode_loadlibrary(void) {
	orig_LoadLibraryA = (struct HINSTANCE__ *(__stdcall*)(const char*)) \
	DetourFunction((LPBYTE)LoadLibraryA, (LPBYTE)hLoadLibraryA);
}
#include "shared.h"
#include "Commctrl.h"
#include "ShlObj.h"
#include "Shlwapi.h"
#include "Shellapi.h"
#include "resource.h"

#include <tchar.h>

static int(__stdcall *main)(HINSTANCE, HINSTANCE, LPSTR, int) = (int(__stdcall*)(HINSTANCE, HINSTANCE, LPSTR, int))0x4640B0;

char sys_cmdline[MAX_STRING_CHARS];
char szAppData[MAX_PATH + 1];

std::vector<threadInfo_t> threadsinfo;
bool thrIsExit = false;

extern HMODULE hModule;
HINSTANCE hInst;

HWND hSplashScreen = (HWND)0x8E5268;

bool bNullClient = false;
bool bDeveloper = false;

HWND g_Dialog = nullptr;
int dwCancelDownload = 0;

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		//EndDialog(hWnd, 0);
		//MessageBoxA(hWnd, "Successfully updated!", __TITLE, MB_OK);

		if (g_Dialog != nullptr) {
			DestroyWindow(g_Dialog);
			g_Dialog = nullptr;
		}
		dwCancelDownload = 1;
		PostQuitMessage(0);
		break;

	case WM_INITDIALOG: {
		SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETRANGE, 1, MAKELONG(0, 100));
		SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETSTEP, 0, 0);
		//SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_STEPIT, 0, 0);
		} return 0;

	default:
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI thr_LoadingBar(LPVOID parm) {
	HWND hWnd;
	//DialogBoxParam(hInstance, MAKEINTRESOURCEA(IDD_DIALOGBAR), NULL, (DLGPROC)DlgProc, (LPARAM)NULL);
	g_Dialog = CreateDialogA(hModule, MAKEINTRESOURCEA(IDD_DIALOGBAR), NULL, (DLGPROC)DlgProc);

	if (g_Dialog != nullptr)
		ShowWindow(g_Dialog, SW_NORMAL);
	else
		return 0;
	MSG msg;
	while (!thrIsExit && GetMessageA(&msg, NULL, 0, 0)) {
		if (!IsDialogMessage(g_Dialog, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (g_Dialog != nullptr)
		DestroyWindow(g_Dialog);
	return 0;
}

void RemoveThread(threadInfo_t *ti) {
	if (!ti)
		return;
	DWORD exitCode;
	for (auto it = threadsinfo.begin(); it != threadsinfo.end();) {
		if (it->handle == ti->handle) {
			if (GetExitCodeThread(it->handle, &exitCode) != 0) {
				if (exitCode == STILL_ACTIVE) {
					//MessageBox(NULL, va("waiting on thread %d", it->id), __TITLE, MB_OK);
					if (WaitForSingleObject(it->handle, INFINITE) != WAIT_OBJECT_0)
						MsgBox("fail wait");
				}
				CloseHandle(it->handle);
			}
			it = threadsinfo.erase(it);

			break;
		}
		else
			++it;
	}
}

void CleanupThreads() {
	thrIsExit = true;

	DWORD exitCode;
	for (std::vector<threadInfo_t>::iterator it = threadsinfo.begin(); it != threadsinfo.end();) {
		if (!it->handle)
			goto just_del;
		if (GetExitCodeThread(it->handle, &exitCode) != 0) {
			if (exitCode == STILL_ACTIVE) {
				//MessageBox(NULL, va("waiting on thread %d", it->id), __TITLE, MB_OK);
				if (WaitForSingleObject(it->handle, INFINITE) != WAIT_OBJECT_0)
					MsgBox("fail wait");
			}
			CloseHandle(it->handle);
			just_del:
			it->handle = NULL;
			it = threadsinfo.erase(it);
			continue;
		}
		++it;
	}

	//MsgBox("cleaned up closing process now\n");
}

threadInfo_t *AddThread(std::string key, DWORD(WINAPI *thr_func)(LPVOID)) {
	threadInfo_t ti;
	ti.key = key;
	ti.handle = (HANDLE)CreateThread(0, 0, thr_func, 0, 0, &ti.id);
	int idx = threadsinfo.size();
	threadsinfo.push_back(ti);
	return &threadsinfo[idx];
}

int create_progress_download(const char *url, FILE *fp, int(*progress_callback)(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow));

static int dl_progress_cb(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
	//SendDlgItemMessage(g_Dialog, IDC_PROGRESS1, PBM_SETRANGE, 1, MAKELONG(0, 10));
	SendDlgItemMessage(g_Dialog, IDC_PROGRESS1, PBM_SETPOS, (WPARAM)(dlnow/dltotal*100), 0);
	SendDlgItemMessage(g_Dialog, IDC_PROGRESS1, PBM_STEPIT, 0, 0);
	Sleep(20); //just to put here to make it seem cooler
	return dwCancelDownload;
}

bool Sys_UpdateExtended(const char *uri) {
	int Sys_IsAdmin();
	if (!Sys_IsAdmin()) {
		void Sys_ElevateProgram();
		Sys_ElevateProgram();
		return false;
	}

	char *fn, *path;
	Sys_GetModulePathInfo(NULL, &path, &fn, NULL);

	char szUpdateFile[MAX_PATH + 1] = { 0 };
	_snprintf(szUpdateFile, MAX_PATH, "%s\\codupdatefile.%u", szAppData, (unsigned)rand());

#define DEST_FILE "mss32.dll"

	FILE *fp = fopen(szUpdateFile, "wb");

	if (fp == nullptr)
		return false;

	threadInfo_t *thr = AddThread("loadingbar", thr_LoadingBar);
	
	if (create_progress_download(uri, fp, dl_progress_cb) == 42) {
		MessageBoxA(NULL, "Cancelled updating Call of Duty.", __TITLE, MB_OK | MB_ICONINFORMATION);
		goto fail;
	}
	else {
		char dest_file[MAX_PATH + 1] = { 0 };
		_snprintf(dest_file, MAX_PATH, "%s\\%s", path, DEST_FILE);
#include "version_info.h"
		char *dest_file_old = va("%s\\%s.old", szAppData, DEST_FILE);
		
		if (FileExists(dest_file_old) && !DeleteFileA(dest_file_old))
			goto fail;

		if (!MoveFileA(dest_file, dest_file_old)) {
			goto fail;
		}

		if (!MoveFileA(szUpdateFile, dest_file))
			goto fail;
	}

	SendMessage(g_Dialog, WM_CLOSE, 0, 0);
	WaitForSingleObject(g_Dialog, INFINITE);
	void Sys_RestartProgram(bool);
	Sys_RestartProgram(false);
	return true; // wont reach

fail:

	SendMessage(g_Dialog, WM_CLOSE, 0, 0);
	WaitForSingleObject(g_Dialog, INFINITE);
	Com_Quit_f();
	return false;
}

extern "C" bool bClosing = false;

void Sys_Unload() {
	bClosing = true;
	static bool unloaded = false;

	if (unloaded)
		return;
	unloaded = true;

	void CleanupThreads();
	CleanupThreads();

	void CL_DiscordShutdown();
	CL_DiscordShutdown();
}

void RegistryAddURLProtocol() {
	HKEY hkey;
	char gamePath[MAX_PATH], szExe[MAX_PATH * 2];
	GetModuleFileName(NULL, gamePath, MAX_PATH);
	LPCTSTR defaultIcon = TEXT("CoDMP.exe,0");

	if (RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Classes\\cod1x", &hkey) == ERROR_SUCCESS) {
		RegSetValueExA(hkey, "URL Protocol", 0, REG_SZ, (PBYTE)"", 1);
		RegSetValueExA(hkey, "DefaultIcon", 0, REG_SZ, (LPBYTE)defaultIcon, _tcslen(defaultIcon) * sizeof(TCHAR));
		RegCloseKey(hkey);
	}

	if (RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Classes\\cod1x\\shell\\open\\command", &hkey) == ERROR_SUCCESS) {
		Com_sprintf(szExe, sizeof(szExe), "%s %%1", gamePath);
		RegSetValueA(hkey, NULL, REG_SZ, szExe, strlen(szExe));
		RegCloseKey(hkey);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	hInst = hInstance;
	strncpy(sys_cmdline, lpCmdLine, sizeof(sys_cmdline) - 1);

	// Custom URL protocol: cod1x://1.2.3.4 to connect to a server.
	std::string strCmdLine = std::string(lpCmdLine);
	if (strCmdLine.rfind("cod1x://", 0) == 0) {
		// Remove cod1x:// and ending slash from string.
		strCmdLine.erase(0, 8);
		if (strCmdLine.back() == '/')
			strCmdLine.pop_back();

		// Check is IP valid.
		netadr_t ip;
		if (NET_StringToAdr(strCmdLine.c_str(), &ip)) {
			// Set "connect ip" command to the command line.
			strCmdLine = "connect " + strCmdLine;
			lpCmdLine = const_cast<char*>(strCmdLine.c_str());
		}
	}
	else { // Add the registry keys for the protocol.
		RegistryAddURLProtocol();
}

#ifdef PROJECT_EXE
	threadInfo_t *thr = AddThread("loadingbar", thr_LoadingBar);
	DWORD exitCode = STILL_ACTIVE;
	
	FILE *fp = fopen("C:/Users/R/Desktop/testsounds.pk3", "wb");

	if (fp == nullptr)
		return 0;

	if (create_progress_download("http://cod1.eu/dl/zz_deathrun_sounds.pk3", fp, dl_progress_cb) == 42) {
		MsgBox("cancelled");
	}

	SendMessage(g_Dialog, WM_CLOSE, 0, 0);
	CleanupThreads();
	return 0;
#else
	if (strstr(lpCmdLine, "steamchild") != NULL) {
		return 0;
	}

	if (Sys_GetAppDataFolder(szAppData, MAX_PATH, true) == NULL) {
		MsgBox("Failed to create data folder.");
		return 0;
	}

	void MSS32_Hook();
	MSS32_Hook();

	extern bool miles32_loaded;
	if (!miles32_loaded)
		return 0;

	return main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
#endif
}
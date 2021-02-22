#include "shared.h"
#include "Commctrl.h"
#include "ShlObj.h"
#include "Shlwapi.h"
#include "Shellapi.h"
#include "resource.h"
#include "steam.h"

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
#if 0
HBITMAP DlgBitmap = nullptr;
#endif
int dwCancelDownload = 0;

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		//EndDialog(hWnd, 0);
		//MessageBoxA(hWnd, "Successfully updated!", __TITLE, MB_OK);

#if 0
		if (DlgBitmap != nullptr);
			DeleteObject(DlgBitmap);
#endif
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
#if 0
		DlgBitmap = (HBITMAP)LoadImageA(hModule, MAKEINTRESOURCE(IDB_BITMAP1),
			IMAGE_BITMAP, 0, 0, LR_SHARED | LR_COPYFROMRESOURCE);
		HBITMAP old = (HBITMAP)SendDlgItemMessageA(hWnd, IDC_STATIC4, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)DlgBitmap);
		if (old && old != DlgBitmap)
			DeleteObject(old);
#endif
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
#if 0
#ifdef XTNDED_DEV
	return false;
#endif
#endif

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

	//void DestroyDefaultBrowser();
	//DestroyDefaultBrowser();

	void CleanupThreads();
	CleanupThreads();
	//MsgBox("cleant up threads");

#ifdef uMYSQL
	if (codversion == CODUO_51) {
		void scr_mysql_global_cleanup();
		scr_mysql_global_cleanup();
	}
#endif

	if (cSteamClient != nullptr) {
		delete cSteamClient;
		cSteamClient = nullptr;
	}
	//MsgBox("csteamclient deleted");

	void XUI_Destroy();
	XUI_Destroy();
	//MsgBox("XUI_DESTROYED");

#ifdef DEBUG
	_CrtDumpMemoryLeaks();
	CloseHandle(hLogFile);
#endif
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	hInst = hInstance;
	strncpy(sys_cmdline, lpCmdLine, sizeof(sys_cmdline) - 1);

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

#if 0
	while (g_Dialog != nullptr || WaitForSingleObject(thr->handle, 100) != WAIT_OBJECT_0) {
		//GetExitCodeThread(thr->handle, &exitCode);

		SendDlgItemMessage(g_Dialog, IDC_PROGRESS1, PBM_SETSTEP, 1, 0);
		int cur = SendDlgItemMessageA(g_Dialog, IDC_PROGRESS1, PBM_STEPIT, 0, 0);

		if (cur >= 100) {
			ShowWindow(g_Dialog, SW_HIDE);
			//MsgBox("cur >= 100");
			break;
		}

		Sleep(100);
	}
#endif
	CleanupThreads();
	return 0;


#else
	
	
	
	if (strstr(lpCmdLine, "steamchild") != NULL) {
		return 0;
	}
#ifdef XTNDED_DEV
	char *cmd;

	for (BYTE i = 0; i < __argc; i++) {
		cmd = __argv[i];
		if (!strlen(cmd))
			continue;

		if(!strcmp(cmd, "-name")) {
			if(__argc - 1 == i)
				continue;
			char *name = __argv[++i];
			Com_sprintf(PRODUCT_DISPLAY_NAME_BUF, sizeof(PRODUCT_DISPLAY_NAME_BUF), "%s", name);

		} else if (!strcmp(cmd, "-nullclient")) {
			bNullClient = true;

		}
		else if (!strcmp(cmd, "-dev")) {
			bDeveloper = true;
		}
	}

	if (bNullClient) {
		printf("steam loading...\n");

		cSteamClient = new CSteamClient();

		if (SteamClient() != nullptr) {
			printf("not nullptr\n");

			for (int k = 0; k < SteamFriends()->GetFriendCount(k_EFriendFlagAll); k++) {
				CSteamID friendID = SteamFriends()->GetFriendByIndex(k, k_EFriendFlagAll);

				const char *sFriendName = SteamFriends()->GetFriendPersonaName(friendID);

				if (strstr(sFriendName, "Laugh") || strstr(sFriendName, "nope")) {
					//SteamFriends()->InviteUserToGame(friendID, "top kek");
					break;

				}
			}
		}

		while (1) {

			if (GetAsyncKeyState(VK_LCONTROL)) {
				printf("Exiting!\n");
				return 0;
			}

		}
	}
#endif

	if (Sys_GetAppDataFolder(szAppData, MAX_PATH, true) == NULL) {
		MsgBox("Failed to create data folder.");
		return 0;
	}

	void MSS32_Hook();
	MSS32_Hook();

	extern bool miles32_loaded;
	if (!miles32_loaded)
		return 0;

	void XUI_Init();
	XUI_Init();

	return main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
#endif
}
#include "shared.h"
#include "client.h"
#include "render.h"
#include "version_info.h"
#include "dl_public.h"

#pragma comment(lib, "psapi.lib")

#include "Psapi.h"
#include "Shlwapi.h"

cvar_t *cl_running;
cvar_t *clientname;
cvar_t *cl_wwwDownload;
cvar_t *cl_allowDownload;

cvar_t *cl_console_fraction;
cvar_t *cl_findshader;

cvar_t *cl_font_type;
cvar_t *cg_drawheadnames;
cvar_t *cg_xui_scoreboard;

DWORD __glob_wd_threadid;
HANDLE __glob_wd_threadhandle;
std::string res;

#include <sstream>
#include <cstdint>

void CL_Connect_f() {
	void(*o)() = (void(*)())0x40F6A0;

	o();
	
    if (*cls_state == CA_CONNECTING || *cls_state == CA_CHALLENGING) {
        Cvar_Set("cl_allowDownload", "0");
    }        

    char* info = clc_stringData + clc_stringOffsets[1];
    char *fs_game = Info_ValueForKey(info, "fs_game"); // Reset client fs_game if loaded & server doesn't use it.
	if (fs_game == "") {
		Cvar_Set("fs_game", ""); 
	}
}

void(*CL_DownloadsComplete)(void) = (void(*)())0x40FFB0;

void Need_Paks() {
	return;
}

char* MAX_PACKET_USERCMDS() {
	return false;
}

void DL_Name(const char *localName, char* remoteName) {
	char *downloadName = Cvar_VariableString("cl_downloadName");
	Cvar_Set("cl_downloadName", va("        %s", (char*)remoteName)); // Enough spaces to render name fully. :P
}

static int use_regular_dl = 0;

int dl_files_count = 0;

void WWW_BeginDownload(void) {
	char localTempName[MAX_PATH];
	char remoteTempName[MAX_PATH];

	if (clc_bWWWDl)
		return;

	char *s;
	char *remoteName, *localName;

	char* info = clc_stringData + clc_stringOffsets[1];
	char *url = Info_ValueForKey(info, "sv_wwwBaseURL");

	if (*clc_downloadList) {
		s = clc_downloadList;

		dl_files_count = 0;
		int i;
		for (i = 0; i < strlen(clc_downloadList); i++)
			if (clc_downloadList[i] == '@')
				dl_files_count++;

		// @remotename@localname@remotename@localname, etc.

		if (*s == '@') {
			s++;
		}
		remoteName = s;

		if ((s = strchr(s, '@')) == NULL) {
			CL_DownloadsComplete();
			return;
		}

		*s++ = 0;
		localName = s;
		if ((s = strchr(s, '@')) != NULL) {
			*s++ = 0;
		} else {
			s = localName + strlen(localName); // point at the nul byte
		}

		int tmp = use_regular_dl;
		use_regular_dl = 0;
		if (cl_wwwDownload->integer && url && *url && !tmp) {
			Com_Printf("***** WWW_BeginDownload *****\n"
				"Localname: %s\n"
				"Remotename: %s\n"
				"****************************\n", localName, remoteName);

			Cvar_Set("cl_downloadSize", "0");
			Cvar_Set("cl_downloadCount", "0");
			Cvar_Set("cl_downloadTime", va("%i", *cls_realtime));

			Q_strncpyz(localTempName, FS_BuildOSPath(Cvar_VariableString("fs_homepath"), localName, ""), sizeof(localTempName));
			localTempName[strlen(localTempName) - 1] = '\0';

			Q_strncpyz(remoteTempName, FS_BuildOSPath(url, remoteName, ""), sizeof(remoteTempName));
			remoteTempName[strlen(remoteTempName) - 1] = '\0';

			if (!DL_BeginDownload(localTempName, remoteTempName, 1)) {
				clc_bWWWDl = false;
				const char *error = va("Download failure while getting '%s'\n", remoteTempName); // get the msg before clearing structs

				Com_Error(ERR_DROP, error);
				return;
			}

			clc_bWWWDl = true;
		}

		*cls_downloadRestart = qtrue;

		memmove(clc_downloadList, s, strlen(s) + 1);

		return;
	}

	CL_DownloadsComplete();
}

void X_CL_NextDownload(void) {
	char* info = clc_stringData + clc_stringOffsets[1];
	char *url = Info_ValueForKey(info, "sv_wwwBaseURL");

	if(cl_wwwDownload->integer && *url )
		WWW_BeginDownload();
	else
	    CL_NextDownload();
}

void CL_WWWDownload() {
	dlStatus_t ret = DL_DownloadLoop();

	if (ret == DL_CONTINUE)
		return;

	if (ret == DL_DONE) {
		Cvar_Set("cl_downloadName", "");
		clc_bWWWDl = false;
		*cls_downloadRestart = 1;
		CL_DownloadsComplete();
	} else if (ret == DL_FAILED) {
		// Perhaps actually check the response? Invalid URL, forbidden, etc?
		const char* error = va("Download failure while getting %s.\nURL might be invalid.", Cvar_VariableString("dlname_error"));
		Com_Error(ERR_DROP, error);
		return;
	}
}

void CL_InitDownloads() {
	if (clc_bWWWDl)
		return;

	if (cl_allowDownload->integer && FS_ComparePaks(clc_downloadList, 1024, qtrue)) {
		Com_Printf("Need paks: %s\n", clc_downloadList);
		if (*clc_downloadList) { // if autodownloading is not enabled on the server
			*cls_state = 3;
			CL_NextDownload();
			return;
		}
	}

	CL_DownloadsComplete();
}

void CL_FOVLimit() {
	int fov = Cvar_VariableIntegerValue("cg_fov");
	int cheats = atoi(Info_ValueForKey(cs1, "sv_cheats"));

	char* sv_fov_min = Info_ValueForKey(cs1, "sv_fov_min");
	char* sv_fov_max = Info_ValueForKey(cs1, "sv_fov_max");
	int fovMin = strlen(sv_fov_min) ? atoi(sv_fov_min) : 80;
	int fovMax = strlen(sv_fov_max) ? atoi(sv_fov_max) : 95;

	if ((fov < fovMin || fov > fovMax) && cheats != 1) {
		Com_Printf("cg_fov \"%d\" is invalid. Allowed values: \"%d\" - \"%d\".\n", fov, fovMin, fovMax);
		Cvar_Set("cg_fov", "80");
	}
}

void CL_FPSLimit() {
	char* fps = Cvar_VariableString("com_maxfps");
	if (atoi(fps) < 30 || atoi(fps) > 333) {
		Com_Printf("com_maxfps \"%s\" is invalid. Allowed values: \"30\" - \"333\".\n", fps);
		Cvar_Set("com_maxfps", "60");
	}
}

void Disconnect_IfEsc() {
	if (*cls_state == CA_CONNECTING || *cls_state == CA_CHALLENGING || *cls_state == CA_CONNECTED) {
		if (GetFocus() && GetKeyState(VK_ESCAPE) & 0x8000)
		{
			((void(*)())0x40F5F0)(); //CL_Disconnnect 
		}
	}
}

void CL_Frame(int msec) {
	void(*call)(int);
	*(DWORD*)&call = 0x411280;

	if (!cl_running->integer)
		return;
	
	void Enc_SendHeartbeat();
	Enc_SendHeartbeat();

	if (clc_bWWWDl)
		CL_WWWDownload();

	void CL_DiscordFrame();
	CL_DiscordFrame();

	CL_FOVLimit();
	CL_FPSLimit();
	Disconnect_IfEsc();

	call(msec);
}

int *whiteShader = (int*)0x15CA630;

void CL_Init(void) {
	bool fix_bugs();
	if (!fix_bugs()) {
		MsgBox("failed to fix bugs in default cod1");
		Com_Quit_f();
	}

	void(*oCL_Init)();
	*(int*)(&oCL_Init) = 0x411E60;

	oCL_Init();

	cl_running = Cvar_Get("cl_running", "0", 64);
	clientname = Cvar_Get("name", "Unknown Soldier", 3);
	cl_wwwDownload = Cvar_Get("cl_wwwDownload", "1", CVAR_ARCHIVE);
	cl_allowDownload = Cvar_Get("cl_allowDownload", "0", CVAR_ARCHIVE);
	cl_console_fraction = Cvar_Get("cl_console_fraction", "1.0", CVAR_ARCHIVE);
	cl_findshader = Cvar_Get("cl_findshader", "not-an-existing-shader", 0);
	cl_font_type = Cvar_Get("cl_font_type", "1", CVAR_ARCHIVE);
	cg_drawheadnames = Cvar_Get("cg_drawheadnames", "0", 0);
	cg_xui_scoreboard = Cvar_Get("cg_xui_scoreboard", "0", 0);

	Cvar_Get("xtndedbuild", va("%i", BUILDNUMBER), CVAR_USERINFO | CVAR_ROM);
	Cvar_Set("version", va("COD MP 1.1x build %d %s %s win-x86", BUILDNUMBER, __DATE__, __TIME__));
	Cvar_Set("shortversion", "1.1x");

	Cvar_Get("g_scoreboard_kills", "Kills", 0);
	Cvar_Get("g_scoreboard_deaths", "Deaths", 0);
	Cvar_Get("g_scoreboard_ping", "Ping", 0);
	Cvar_Get("cg_x_obituary", "1", 0);

	Cvar_Set("r_overbrightbits", "0");
	Cvar_Set("r_ignorehwgamma", "0");
	Cvar_Set("cl_languagewarnings", "0");
	Cvar_Set("cl_languagewarningsaserrors", "0");
	Cvar_Set("com_hunkmegs", "512");

	#if 0
		// None of these seem to work.
		char*(__fastcall*CL_TranslateString)(const char *string, char *buf, int);
		*(int*)&CL_TranslateString = 0x4ABF00;
		static const char* (*CL_TranslateStringBuf2)(const char *string, const char *type) = (const char*(*)(const char*,const char*))0x4A9E20;
		MsgBox(CL_TranslateString("EXE_ENDOFGAME",buf,0));
		const char *b = CL_TranslateStringBuf2("CGAME_PRONE_BLOCKED", "cgame");
		if (b == nullptr)
			b = "(null)";
		MsgBox(b);
	#endif
}

void SCR_DrawScreenField(stereoFrame_t stereoFrame) { //TODO fix draw after console
	void(*call)(stereoFrame_t);
	*(int*)(&call) = 0x416DD0;
	call(stereoFrame);

#if 0
	extern FILE* dl_file;
	if (dl_file != NULL) {
		float color[4] = { 1, 1, 1, 1 };
		SCR_DrawString(210, 90, 1, .5, color, va("^3%d ^7downloads left", dl_files_count / 2), NULL, NULL, NULL);
	}
#endif

	void CG_SCR_DrawScreenField(int);
	CG_SCR_DrawScreenField(stereoFrame);
}

char* __cdecl CL_SetServerInfo_HostnameStrncpy(char* a1, char* a2, size_t a3) {
	return strncpy(a1, Com_CleanHostname(a2, true), a3);
}
#include "shared.h"
#include "client.h"
#include "render.h"
#include "version_info.h"
#include "dl_public.h"

#pragma comment(lib, "psapi.lib")

#include "Shlwapi.h"

cvar_t *cl_running;
cvar_t *clientname;
cvar_t *cl_wwwDownload;
cvar_t *cl_allowDownload;
cvar_t *cl_console_fraction;
cvar_t *cl_findshader;

cvar_t *cg_drawheadnames;
cvar_t *cg_fov;
cvar_t* cg_x_discord;

cvar_t* g_bounce;

cvar_t* com_hunkmegs;
cvar_t* x_master;

cvar_t* r_borderless;

DWORD __glob_wd_threadid;
HANDLE __glob_wd_threadhandle;
std::string res;

#include <sstream>

void CL_Connect_f() {
	void(*o)() = (void(*)())0x40F6A0;
	
	o();
	
	if (*cls_state == CA_CONNECTING || *cls_state == CA_CHALLENGING) {
	Cvar_Set("cl_allowDownload", "0");
	}        
	
	char* info = clc_stringData + clc_stringOffsets[1];
	char *fs_game = Info_ValueForKey(info, "fs_game"); // Reset client fs_game if loaded & server doesn't use it.
	if (strlen(fs_game)) {
		Cvar_Set("fs_game", ""); 
	}
}

void(*CL_DownloadsComplete)(void) = (void(*)())0x40FFB0;

void DL_Name(const char *localName, char* remoteName) {
	char *downloadName = Cvar_VariableString("cl_downloadName");
	Cvar_Set("cl_downloadName", va("        %s", remoteName)); // Enough spaces to render name fully. :P
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
				char *error = va("Download failure while getting '%s'\n", remoteTempName); // get the msg before clearing structs

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
	char* url = Info_ValueForKey(info, "sv_wwwBaseURL");
	int argc = Cmd_Argc();

	if (argc > 1) {
		const char* arg1 = Info_ValueForKey(info, "sv_referencedPakNames");

		if (strstr(arg1, ".pk3") != NULL) { //so if extension is not pk3 but is (exe,bat and any other) kick player (So you can't dl .exe,.bat,.cfg)
			Com_Error(ERR_DROP, "It's likely that this server will infect your computer with malware. \n We do not permit connections to such servers in order to protect your security.");
			return;
		}
	}

	if (cl_wwwDownload->integer && *url)
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
	int fps = Cvar_VariableIntegerValue("com_maxfps");
	int cheats = atoi(Info_ValueForKey(cs1, "sv_cheats"));

	char* sv_fps_min = Info_ValueForKey(cs1, "sv_fps_min");
	char* sv_fps_max = Info_ValueForKey(cs1, "sv_fps_max");
	int fpsMin = strlen(sv_fps_min) ? atoi(sv_fps_min) : 30;
	int fpsMax = strlen(sv_fps_max) ? atoi(sv_fps_max) : 333;

	if ((fps < fpsMin || fps > fpsMax) && cheats != 1) {
		Com_Printf("com_maxfps \"%d\" is invalid. Allowed values: \"%d\" - \"%d\".\n", fps, fpsMin, fpsMax);
		Cvar_Set("com_maxfps", "85");
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
	if (cg_x_discord->integer)
		CL_DiscordFrame();

	CL_FOVLimit();
	CL_FPSLimit();
	Disconnect_IfEsc();

	call(msec);
}

void Cmd_Borderless() {
	if (Cmd_Argc() > 1) {
		Cvar_Set("r_borderless", Cmd_Argv(1));

		if (Cvar_VariableIntegerValue("r_borderless")) {
			Cvar_Set("r_fullscreen", "0");
			Cvar_Set("r_mode", "-1");
			Cvar_Set("com_introplayed", "1");
		}

		void(*Cbuf_ExecuteText)(const char*);
		*(UINT32*)&Cbuf_ExecuteText = 0x428A80;
		char cmd[10];
		sprintf(cmd, "vid_restart", cmd);
		Cbuf_ExecuteText(cmd);
	}
	else {
		Com_Printf("\"r_borderless\" is:\"%d\" default: \"0\"\n", Cvar_VariableIntegerValue("r_borderless"));
	}
}

void Cmd_Minimize() {
	ShowWindow(*gameWindow, SW_MINIMIZE);
}

int *whiteShader = (int*)0x15CA630;

const char* CL_GetConfigString(int index) {
	// Check if the index is within bounds
	if (index < 0 || index >= 2048) {
		Com_Error(ERR_FATAL, "GetConfigString index out of bounds");
	}

	// Calculate the offset based on the index
	int offset = clc_stringOffsets[index];

	// Check if the offset is zero (empty string)
	if (!offset) {
		return "";
	}

	// Return the actual config string
	return clc_stringData + offset;
}

void CL_OpenScriptMenu(void)
{
	char* parentMenuName;
	const char* scriptMenuResponse;
	int menuIndex;
	char* command;
	int* dword_163B3E0 = (int*)(0x163B3E0);
	int* dword_161747C = (int*)(0x161747C);

	if (Cmd_Argc() == 3)
	{
		if (*(dword_163B3E0 + 32))
		{
			if (dword_161747C)
			{
				parentMenuName = Cmd_Argv(1);
				scriptMenuResponse = Cmd_Argv(2);

				if (parentMenuName && scriptMenuResponse)
				{
					menuIndex = -1;
					for (int i = 0; i < 32; ++i) {
						const char* configString = CL_GetConfigString(i + 1180);

						if (*configString && !I_stricmp(parentMenuName, configString)) {
							menuIndex = i;
							break;
						}
					}

					if (menuIndex != -1) {
						int serverId = Cvar_VariableIntegerValue("sv_serverId");
						command = va("cmd mr %i %i %s\n", serverId, menuIndex, scriptMenuResponse);
						void(*Cbuf_ExecuteText)(const char*);
						*(UINT32*)&Cbuf_ExecuteText = 0x428A80;
						Cbuf_ExecuteText(command);
					}
					else {
						Com_Printf("Menu '%s' not found!\n", parentMenuName);
					}
				}
			}
		}
	}
	else
	{
		Com_Printf("USAGE: openScriptMenu <parent menu name> <script menu response>\n");
		Com_Printf("EXAMPLE: openScriptMenu quickcommands 1\n");
	}
}

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
	cg_drawheadnames = Cvar_Get("cg_drawheadnames", "0", 0);
	cg_fov = Cvar_Get("cg_fov", "80", CVAR_ARCHIVE);
	cg_x_discord = Cvar_Get("cg_x_discord", "1", CVAR_LATCH | CVAR_ARCHIVE);
	com_hunkmegs = Cvar_Get("com_hunkmegs", "128", CVAR_LATCH | CVAR_ARCHIVE);
	x_master = Cvar_Get("x_master", "0", CVAR_ARCHIVE);
	g_bounce = Cvar_Get("g_bounce", "0", CVAR_ARCHIVE);

	Cvar_Get("cg_thirdperson", "0", CVAR_ARCHIVE);
	Cvar_Set("version", va("COD MP 1.1x build %d %s %s win-x86", BUILDNUMBER, __DATE__, __TIME__));
	Cvar_Set("shortversion", va("1.1x (%d)", BUILDNUMBER));

	Cvar_Get("cg_x_obituary", "1", 0);
	Cvar_Get("r_borderless", "0", CVAR_ARCHIVE);

	Cmd_AddCommand("r_borderless", Cmd_Borderless);
	Cmd_AddCommand("minimize", Cmd_Minimize);
	Cmd_AddCommand("openScriptMenu", CL_OpenScriptMenu);

	Cvar_Set("r_overbrightbits", "0");
	Cvar_Set("r_ignorehwgamma", "0");
	Cvar_Set("cl_languagewarnings", "0");
	Cvar_Set("cl_languagewarningsaserrors", "0");

	void CL_DiscordInitialize();
	if (cg_x_discord->integer)
		CL_DiscordInitialize();
}

void SCR_DrawScreenField(stereoFrame_t stereoFrame) { //TODO fix draw after console
	void(*oSCR_DrawScreenField)(stereoFrame_t);
	*(int*)(&oSCR_DrawScreenField) = 0x416DD0;
	oSCR_DrawScreenField(stereoFrame);

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

void CL_GlobalServers_f(void) {
	if (Cmd_Argc() < 3) {
		Com_Printf("usage: globalservers <master# 0-1> <protocol> [keywords]\n");
		return;
	}

	/*
	if (x_master->integer) {
		void XMaster_GetServers();
		XMaster_GetServers();
	}
	*/

	netadr_t to;
	int i;
	int count;
	char* buffptr;
	char command[1024];

	*cls_numglobalservers = -1;
	*cls_pingUpdateSource = 1;

	if (x_master->integer) {
		if (NET_StringToAdr("cod.pm", &to)) {
			Com_Printf("Requesting servers from CoD 1.1x master...\n");
		}
	}
	else {
		if (NET_StringToAdr("codmaster.activision.com", &to)) {
			Com_Printf("Requesting servers from codmaster.activision.com...\n");
		}
	}

	short BigShort(short);
	to.type = NA_IP;
	to.port = BigShort(20510);

	sprintf(command, "getservers %s", Cmd_Argv(2));

	buffptr = command + strlen(command);
	count = Cmd_Argc();
	for (i = 3; i < count; i++)
		buffptr += sprintf(buffptr, " %s", Cmd_Argv(i));

	NET_OutOfBandPrint(NS_SERVER, to, command);
}

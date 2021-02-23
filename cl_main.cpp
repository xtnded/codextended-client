#include "shared.h"
#include "client.h"
#include "render.h"
#include "steam.h"
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

#define STEAM_CLOUD_FILENAME "data"

void _steam_set() {
	if (Cmd_Argc() != 2) {
		Com_Printf("noob\n");
		return;
	}

	char *msg = Cmd_Argv(1);
	SteamRemoteStorage()->FileWrite(STEAM_CLOUD_FILENAME, msg, strlen(msg) + 1);

}
void _steam_get() {
	char buf[1024] = { 0 };
	if (!SteamRemoteStorage()->FileExists(STEAM_CLOUD_FILENAME)) {
		Com_Printf("^1no file!\n");
		return;
	}
	int32 fs = SteamRemoteStorage()->GetFileSize(STEAM_CLOUD_FILENAME);
	if (fs >= sizeof(buf)) {
		Com_Printf("too large\n");
		return;
	}
	int32 read_size = SteamRemoteStorage()->FileRead(STEAM_CLOUD_FILENAME, buf, sizeof(buf) - 1);
	buf[read_size] = '\0';
	Com_Printf("data = %s\n", buf);
}

DWORD __glob_wd_threadid;
HANDLE __glob_wd_threadhandle;
std::string res;

DWORD WINAPI dog_thr(LPVOID parm) {
	if (!(res = GetOpenFileNameS(NULL)).length())
		MsgBox("none!");
	else
		Com_Printf("res = %s\n", res.c_str());

	
	MsgBox("returning m8");
	return 0;
}

DWORD WINAPI loop_thr(LPVOID a) {
	while (!thrIsExit) {

		Com_Printf("msg m8!!\n");
		Sleep(3000);
	}

	return 0;
}


#include <sstream>
#include <cstdint>

class KeyValuesBuilder
{
private:
	std::stringstream m_buffer;

	inline void PackBytes(const void* bytes, size_t size)
	{
		m_buffer << std::string(reinterpret_cast<const char*>(bytes), size);
	}

	inline void PackDataType(uint8_t type)
	{
		PackBytes(&type, 1);
	}

	inline void PackNullTerminated(const char* string)
	{
		PackBytes(string, strlen(string) + 1);
	}

public:
	inline void PackString(const char* key, const char* value)
	{
		PackDataType(1);
		PackNullTerminated(key);
		PackNullTerminated(value);
	}

	inline void PackUint64(const char* key, uint64_t value)
	{
		PackDataType(7);
		PackNullTerminated(key);
		PackBytes(&value, sizeof(value));
	}

	inline void PackEnd()
	{
		PackDataType(8);
	}

	inline std::string GetString()
	{
		return m_buffer.str();
	}
};

void list_dll() {

	return;
#if 1
	/* experimental half working steam stuff */
	HMODULE hsteamclient = GetModuleHandleA("steamclient.dll");

#define STEAM_OFF(x) ((int)hsteamclient + (x - 0x38000000))

	if (hsteamclient != NULL) {

		Com_Printf("steam client present!\n");
		
#if 0
		int returnCode;

		void*(*SteamAPI_CreateInterface)(const char*, int*);
		*(uint32_t*)&SteamAPI_CreateInterface = (uint32_t)GetProcAddress(hsteamclient, "CreateInterface");

		if (!SteamAPI_CreateInterface) {
			Com_Printf("createinterface not found\n");
			return;
		}

		void *InterfaceSteamShortcuts = SteamAPI_CreateInterface("CLIENTSHORTCUTS_INTERFACE_VERSION001", &returnCode);
		Com_Printf("returncode = %d, interface steam shortcuts = %02X\n", returnCode, (uint32_t)InterfaceSteamShortcuts);
#endif

		UINT32(*GetSteamFunc)(const char*, const char*);
		*(UINT32*)&GetSteamFunc = STEAM_OFF(0x38254E70);

		UINT32 found, appID;
		

		//found = GetSteamFunc("IClientShortcuts", "GetUniqueLocalAppId");
#if 0
		found = GetSteamFunc("IClientShortcuts", "GetUniqueLocalAppId");

		uint32_t(*GetUniqueLocalAppId)();
		*(int*)&GetUniqueLocalAppId = found;

		if (!found) {
			Com_Printf("not found error\n");
			return;
		}
		//appID = GetUniqueLocalAppId();
#endif
		appID = STEAM_APPID;

		found = GetSteamFunc("IClientApps", "SetLocalAppConfig"); //found so far

		Com_Printf("found = %02X\n", found);

		int parentAppId = STEAM_APPID;
#if 1
		if (!SteamApps()->BIsSubscribedApp(parentAppId))
			parentAppId = 218;
#endif

		// create a fake app to hold our gameid
		uint64_t gameID = 0xA18F2DAB01000000 | parentAppId; // crc32 for 'kekking' + mod

		// create the keyvalues string for the app
		KeyValuesBuilder builder;
		builder.PackString("name", "i like penguins");
		builder.PackUint64("gameid", gameID);
		builder.PackString("installed", "1");
		builder.PackString("gamedir", "kekking");
		builder.PackString("serverbrowsername", "lovely!");
		builder.PackEnd();

		std::string str = builder.GetString();

		bool(*SetLocalAppConfig)(uint32_t, const char*, uint32_t);
		*(UINT32*)&SetLocalAppConfig = found;

		bool result;
		for (uint32_t i = 0; i < UINT32_MAX; i++)
		result = SetLocalAppConfig(i, str.c_str(), (uint32_t)str.size());
		//bool configAdded = steamAppsInterface.Invoke<bool>("SetLocalAppConfig", appID, str.c_str(), (uint32_t)str.size());
		if (result) {
			Com_Printf("configAdded\n");
		}
		else {
			Com_Printf("not added\n");
		}
	}
	return;
#endif
		char xn[MAX_PATH];
		char modname[MAX_PATH];
		HMODULE mods[1024];
		HANDLE proc = GetCurrentProcess();
		DWORD cbNeeded;
		unsigned int i;
		if (EnumProcessModules(proc, mods, sizeof(mods), &cbNeeded)) {
			for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
				if (GetModuleFileNameEx(proc, mods[i], modname, sizeof(modname) / sizeof(char))) {
					//Com_Printf("^3%s\n", modname);

					if (strstr(modname, "xfire_toucan")) {


						int(*ToucanGetBuildNumber)() = NULL;
						HMODULE hModule = GetModuleHandleA(modname);
						if (hModule != NULL) {
							ToucanGetBuildNumber = (int(*)())GetProcAddress(hModule, "ToucanGetBuildNumber");


							if (ToucanGetBuildNumber != NULL) {
								Com_Printf("build num = %d\n", ToucanGetBuildNumber());
							}
						}
					}
				}
			}
		}

		threadInfo_t ti;
		ti.key = "open_file_thread";
		ti.handle = (HANDLE)CreateThread(0, 0, dog_thr, 0, 0, &ti.id);
		threadsinfo.push_back(ti);
}

#if 0

void istate() {
	FriendGameInfo_t fgi;
	CSteamID fid;
	int iFriendFlags = k_EFriendFlagAll;
	size_t friend_count = SteamFriends()->GetFriendCount(iFriendFlags);
	for (size_t i = 0; i < friend_count; i++) {
		fid = SteamFriends()->GetFriendByIndex(i, iFriendFlags);
		//SteamUser()->UserHasLicenseForApp(SteamUser()->GetSteamID(), );

		const char *friend_name = SteamFriends()->GetFriendPersonaName(fid);

		if (strstr(friend_name, "iState") != NULL) {
			//Com_Printf("Friend (%s) is in game %d and ^2%d\n", SteamFriends()->GetFriendPersonaName(fid), fgi.m_gameID, (SteamUser()->UserHasLicenseForApp(fid, STEAM_APPID) == k_EUserHasLicenseResultHasLicense) ? 1 : 0);
			if (SteamUser()->UserHasLicenseForApp(fid, STEAM_COD1_APPID) == k_EUserHasLicenseResultHasLicense) {
				Com_Printf("%s heeft CoD1 op steam\n", friend_name);
			}
			else
				Com_Printf("%s heeft cod1 niet hijs een noob\n", friend_name);
		}

	}
}

#endif

void CL_Connect_f() {
	void(*o)() = (void(*)())0x40F6A0;

	o();
	
    if (*cls_state == CA_CONNECTING || *cls_state == CA_CHALLENGING) {
        Cvar_Set("cl_allowDownload", "0");
    }        

    char* info = clc_stringData + clc_stringOffsets[1];
    char *fs_game = Info_ValueForKey(info, "fs_game"); //If servers fs_game is not set(no mods) but client has fs_game set to some value it's gonna restart it to "" so he won't get custom huds from last modded server he was connected to
	if (fs_game == "") {
		Cvar_Set("fs_game", fs_game); 
	}
}

void(*CL_DownloadsComplete)(void) = (void(*)())0x40FFB0;
void(*CL_BeginDownload)(const char*, const char*) = (void(*)(const char*, const char*))0x4100D0;

static int use_regular_dl = 0;

int dl_files_count = 0;

void CL_NextDownload(void) {
	char localTempName[MAX_PATH];
	char remoteTempName[MAX_PATH];
#if 0
	void(*nextdl)(void);
	*(int*)&nextdl = 0x410190;
	nextdl();
#endif

	if (clc_bWWWDl)
		return;

	char *s;
	char *remoteName, *localName;

	char* info = clc_stringData + clc_stringOffsets[1];

	char *url = Info_ValueForKey(info, "sv_wwwBaseURL");
	// We are looking to start a download here
	if (*clc_downloadList) {
		s = clc_downloadList;


		dl_files_count = 0;

		int i;
		for (i = 0; i < strlen(clc_downloadList); i++)
			if (clc_downloadList[i] == '@')
				dl_files_count++;

		// format is:
		//  @remotename@localname@remotename@localname, etc.

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
		}
		else {
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
				//goto default_dl;
			}

			clc_bWWWDl = true;
		}
		else {
			char downloadURL[MAX_OSPATH];
			char baseURL[MAX_OSPATH];
			int clc_downloadBlock;
			int clc_downloadCount;
			int downloadSize;
			char downloadList[MAX_INFO_STRING];
			Com_Printf("***** BeginDownload *****\n"
				"Localname: %s\n"
				"Remotename: %s\n"
				"****************************\n", localName, remoteName);
			Com_sprintf(downloadURL, sizeof(downloadURL), "%s/%s", baseURL, remoteName);
			strncpy(cls_downloadName, localName, sizeof(cls_downloadName));
			Com_sprintf(cls_downloadTempName, sizeof(cls_downloadTempName), "%s.tmp", localName);

			// Set so UI gets access to it
			Cvar_Set("cl_downloadName", va("        %s", (char*)remoteName));
			Cvar_Set("cl_downloadSize", "0");
			Cvar_Set("cl_downloadCount", "0");
			Cvar_Set("cl_downloadTime", va("%i", *cls_realtime));

			clc_downloadBlock = 0; // Starting new file
			clc_downloadCount = 0;

			CL_AddReliableCommand(va("download %s", remoteName));
			//const char *error = va("Download failure while getting '%s'\n", localName);

			//Com_Error(ERR_DROP, error);
			//return;
		}

		*cls_downloadRestart = qtrue;

		// move over the rest
		memmove(clc_downloadList, s, strlen(s) + 1);

		return;
	}

	CL_DownloadsComplete();
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
	}
	else {
		//const char *error = va( "Download failure while getting '%s'\n", Cvar_VariableString("cl_downloadName") ); // get the msg before clearing structs
		clc_bWWWDl = false;
		use_regular_dl = 1;

		//((void(*)())0x40F5F0)(); //CL_Disconnect_f
		//Com_Error(ERR_DROP, error);
	}
	((void(*)())0x40F640)(); //CL_Reconnect_f
}

void CL_InitDownloads() {
	if (clc_bWWWDl)
		return;

	if (cl_allowDownload->integer && FS_ComparePaks(clc_downloadList, 1024, qtrue)) {
		// this gets printed to UI, i18n
		Com_Printf("Need paks: %s\n", clc_downloadList);

		if (*clc_downloadList) {
			// if autodownloading is not enabled on the server
			*cls_state = 3;
			CL_NextDownload();
			return;
		}
	}

	CL_DownloadsComplete();
}

//#include "Browser/Browser.h"

void CL_Frame(int msec) {
	void(*call)(int);
	*(DWORD*)&call = 0x411280;

	if (!cl_running->integer)
		return;
	
#if 0
	Browser *br = GetDefaultBrowser();
	if(br!=nullptr)
	br->Update();
#endif
	
	void Enc_SendHeartbeat();
	Enc_SendHeartbeat();

	if (bSteamAvailable) {
		cSteamClient->RunFrame();

		if (*Cvar_VariableString("cl_ingame") == '1' && *cls_servername) {
			qboolean    NET_CompareAdr(netadr_t a, netadr_t b);
			netadr_t serverAddress = *clc_serverAddress;
			if (cSteamClient->bIsAdvertisingServer || !NET_CompareAdr(cSteamClient->advertisedServer, serverAddress)) {
				SteamUser()->AdvertiseGame(k_steamIDNonSteamGS, ntohl(serverAddress._ip), ntohs(serverAddress.port));
				cSteamClient->advertisedServer = serverAddress;
				cSteamClient->bIsAdvertisingServer = true;
			}
		}
		else {
			if (cSteamClient->bIsAdvertisingServer) {
				cSteamClient->bIsAdvertisingServer = false;
				SteamUser()->AdvertiseGame(k_steamIDNil, 0, 0);
			}
		}
	}

	if (clc_bWWWDl)
		CL_WWWDownload();
#if 0
	X_DEAD = true;
	__try {
		__asm cli
	}
	__except (1) {
		X_DEAD = 0;
	}

	if (X_DEAD)
		XCRASH

		DWORD res = WaitForSingleObject(__glob_wd_threadhandle, 0);

	if (res == WAIT_OBJECT_0)
		ExitProcess(5);
#endif
	call(msec);
}

int *whiteShader = (int*)0x15CA630;

void Steam_Invite() {
	void(*Cbuf_ExecuteText)(const char*);
	*(UINT32*)&Cbuf_ExecuteText = 0x428A80;

	if (!bSteamAvailable) {
		Com_Printf("Steam not loaded.\n");
		return;
	}

	if (Cmd_Argc() < 3) {
		Com_Printf("usage: %s <substr name> <server ip>\n", Cmd_Argv(0));
		return;
	}
	char *substr = Cmd_Argv(1);
	char *server = Cmd_Argv(2);

	for (int i = 0; i < SteamFriends()->GetFriendCount(k_EFriendFlagAll); i++) {
		CSteamID friendID = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagAll);

		if (!friendID.IsValid())
			continue;

		const char *sFriendName = SteamFriends()->GetFriendPersonaName(friendID);

		if (!sFriendName || !*sFriendName)
			continue;


		FriendGameInfo_t fgi;
		if (strstr(sFriendName, substr) != NULL) {

			if (SteamFriends()->GetFriendGamePlayed(friendID, &fgi)) {
				SteamFriends()->InviteUserToGame(friendID, server);
				Com_Printf("Invited %s", SteamFriends()->GetFriendPersonaName(friendID));
			}
			break;
		}
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
#ifdef FIX_RE

	extern char CRC_MEMID1_buf[0x2be];
	extern unsigned int CRC_MEMID1_crc;
	_memcpy(&CRC_MEMID1_buf[0], (void*)0x439650, 0x2BE);
	CRC_MEMID1_crc = crc32.FullCRC((const unsigned char*)CRC_MEMID1_buf, 0x2be);

#endif

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

#if 0
	void Sys_ElevateProgram();
	Sys_ElevateProgram();
#endif
#if 0

	char*(__fastcall*CL_TranslateString)(const char *string, char *buf, int);
	*(int*)&CL_TranslateString = 0x4ABF00;

	static const char* (*CL_TranslateStringBuf2)(const char *string, const char *type) = (const char*(*)(const char*,const char*))0x4A9E20;

	char buf[32000] = { 0 };
	//MsgBox(CL_TranslateString("EXE_ENDOFGAME",buf,0));
	const char *b = CL_TranslateStringBuf2("CGAME_PRONE_BLOCKED", "cgame");
	if (b == nullptr)
		b = "(null)";
	MsgBox(b);

	//MsgBox(buf);
#endif

#if 1
	if (cSteamClient == nullptr)
		cSteamClient = new CSteamClient();
#endif

#if 0
	if (bSteamAvailable) {
		void print_steam_info();
		Cmd_AddCommand("steam", print_steam_info);
		Cmd_AddCommand("steam_set", _steam_set);
		Cmd_AddCommand("steam_get", _steam_get);
		Cvar_Set("name", (char*)SteamFriends()->GetPersonaName());
		Cmd_AddCommand("invite", Steam_Invite);
		Cmd_AddCommand("dll", list_dll);
	}
#endif
}

#ifdef STEAM_SUPPORT
void print_steam_info() {

	CSteamID id = SteamUser()->GetSteamID();


	Com_Printf("steamid = %lu\n", id);

	Com_Printf("^3hello %s\n", SteamFriends()->GetPersonaName());

	Com_Printf("steam level = %d\n", SteamUser()->GetPlayerSteamLevel());

	CSteamID st_id = SteamUser()->GetSteamID();
	//SteamUser()->AdvertiseGame(st_id, 1, 28960);
	//SteamMatchmaking()->CreateLobby(k_ELobbyTypeFriendsOnly,)

	FriendGameInfo_t fgi;
	CSteamID fid;
	int iFriendFlags = k_EFriendFlagAll;
	size_t friend_count = SteamFriends()->GetFriendCount(iFriendFlags);
	for (size_t i = 0; i < friend_count; i++) {
		fid = SteamFriends()->GetFriendByIndex(i, iFriendFlags);
		//SteamUser()->UserHasLicenseForApp(SteamUser()->GetSteamID(), );

		if (SteamFriends()->GetFriendGamePlayed(fid, &fgi)) {

			Com_Printf("Friend (%s) is in game %d and ^2%d\n", SteamFriends()->GetFriendPersonaName(fid), fgi.m_gameID, (SteamUser()->UserHasLicenseForApp(fid, STEAM_APPID) == k_EUserHasLicenseResultHasLicense) ? 1 : 0);

		}

	}

}
#endif

void SCR_DrawScreenField(stereoFrame_t stereoFrame) { //TODO fix draw after console
	void(*call)(stereoFrame_t);
	*(int*)(&call) = 0x416DD0;
	call(stereoFrame);

#if 0
	duk_push_global_object(js_ctx);
	if (duk_get_prop_string(js_ctx, -1, "scr_drawscreenfield")) {
		duk_push_int(js_ctx, *cls.state);
		if (DUK_EXEC_SUCCESS != duk_pcall(js_ctx, 1)) {
			Com_Error(0, "error: %s\n", duk_to_string(js_ctx, -1));
		}
	}
	duk_pop(js_ctx);
#endif

	switch (*cls_state) {
	case CA_UNINITIALIZED: {

#if 0
		static int BOX_TXT_SIZE = site_motd.size();
		static int BOX_MAX_WIDTH = BOX_TXT_SIZE + 640;
		static int time_box = *cls.realtime;
		static int BOX_X = -BOX_TXT_SIZE;
		static int times = 0;
		if (!site_motd.empty() && times < 40) {
			if (*cls.realtime - time_box > 50) {
				time_box = *cls.realtime;
				++times;
				BOX_X = (BOX_X + 5) % BOX_MAX_WIDTH;
			}
			//Com_Printf("cls_realtime = %d | difference = %d\n", *cls_realtime, (*cls_realtime-time_box));
			int handle = RE_RegisterShaderNoMip("black");
			if (handle != 0) {
				float color2[4] = { 1, 1, 1, .5 };
				RE_SetColor(color2);
				SCR_DrawPic(0, 452, 640, 20, handle);
				RE_SetColor(NULL);
				float color[4] = { 1, 1, 1, 1 };
				SCR_DrawString(BOX_X - BOX_TXT_SIZE, 468, xtext_type->integer, xtext_size->value, color, site_motd.c_str(), NULL, NULL, NULL);
			}
		}
#endif
	}
						   break;

	case CA_CONNECTED: {
	}
					   break;
	}

#if 0
	/*
	void __draw_strings();
	__draw_strings();
	*/
	extern FILE *dl_file;

	if (dl_file != NULL) {

		float color[4] = { 1, 1, 1, 1 };
		SCR_DrawString(210, 90, 1, .5, color, va("^3%d ^7downloads left", dl_files_count / 2), NULL, NULL, NULL);

	}
#endif
	void CG_SCR_DrawScreenField(int);
	CG_SCR_DrawScreenField(stereoFrame);
}
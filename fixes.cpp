#include "shared.h"

static void CLUI_GetCDKey(char* buf, int buflen) {
	MessageBoxA(NULL, "If you wish to change your CD-Key, edit the 'codkey' file.\nThis is to prevent servers from stealing your CD-Key.\nIf you see this message and you aren't changing your key then the server is trying to steal your CD-Key.", __TITLE, 0);
}

bool fix_bugs() {
	bool ret = true;
	__call(0x41892B, (int)CLUI_GetCDKey); //self explainatory?

	void DL_Name(const char *localName, char* remoteName); //fix for not full download name on slow dl
	__call(0x41011C, (int)DL_Name);

	// NOP out the calls to CL_Motd (crash upon startup net not loaded and socket being sent or smth)
	__nop(0x40F6DA, 0x40F6DA + 5);
	__nop(0x4117B6, 0x4117B6 + 5);
	
	__nop(0x411815, 1);

	/* annoying bugs */
	__nop(0x42D122, 5); //call Com_AppendCDKey (fixes the invalid cdkey with fs_game)
	__nop(0x40BC18, 5); //fixes spam with "MAX_PACKET_USERCMDS" if you have 1000 fps
	__nop(0x43BA04, 5); //Removing second "Need Paks:" because it's useless one is enough

	return ret;
}

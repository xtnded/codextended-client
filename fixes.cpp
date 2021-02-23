#include "shared.h"

static void CLUI_GetCDKey(char* buf, int buflen) {
	MessageBoxA(NULL, "If you wish to change your CD-Key, edit the 'codkey' file.\nThis is to prevent servers from stealing your CD-Key.\nIf you see this message and you aren't changing your key then the server is trying to steal your CD-Key.", __TITLE, 0);
	/*
	void (*o)() = (void(*)())0x4180C0;
	o();
	*/
}

bool fix_bugs() {
	bool ret = true;
	__call(0x41892B, (int)CLUI_GetCDKey); //self explainatory?
	//__jmp(0x4180C0, (int)CLUI_GetCDKey);	


	// NOP out the calls to CL_Motd (crash upon startup net not loaded and socket being sent or smth)
	__nop(0x40F6DA, 0x40F6DA + 5);
	__nop(0x4117B6, 0x4117B6 + 5);


	/* annoying bugs */
	__nop(0x42D122, 5); //call Com_AppendCDKey (fixes the invalid cdkey with fs_game)

	/*
	in

	Com_ReadCDKey( BASEGAME );
	fs = Cvar_Get( "fs_game", "", CVAR_INIT | CVAR_SYSTEMINFO );
	if ( fs && fs->string[0] != 0 ) {
	Com_AppendCDKey( fs->string );
	}
	*/

	return ret;
}
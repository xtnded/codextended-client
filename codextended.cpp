#include "shared.h"
#include <WinSock2.h>

//extern "C" DLL_EXPORT void xtnded() {}

bool apply_hooks();

bool determine_cod_version();
bool find_cod_version();

/* any text with __dev__ must be fixed before release */

#define ENABLE_CODX

void codextended() {
	srand(time(NULL));


	if (GetModuleHandleA("codextended.dll") != NULL) {
		//MsgBox("not null!");
		return;
	}

#if 1
	if (!determine_cod_version()) {
		if (!find_cod_version()) {
			MsgBox("Failed to find Call of Duty version, please report this at http://xtnded.org");
			return;
		}
		//MsgBox("Failed to detect CoD version");
	}
#endif

	//MessageBox(NULL, va("v = %s\n", get_codversion_string()), "", 0);
	
#ifdef uMYSQL
	if (codversion == CODUO_51) {
		void mysql_test();
		//mysql_test();
		void scr_mysql_global_startup();
		scr_mysql_global_startup();
	}
#endif

#ifdef ENABLE_CODX
	if (!apply_hooks()) {
		MsgBox("Failed to initialize CoDExtended, please report this at http://xtnded.org\n");
		Com_Quit_f();
	}

#endif
}

void codextended_unload() {
}
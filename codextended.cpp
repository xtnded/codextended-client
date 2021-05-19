#include "shared.h"
#include <WinSock2.h>

bool apply_hooks();

bool determine_cod_version();
bool find_cod_version();

/* any text with __dev__ must be fixed before release */

#define ENABLE_CODX

void codextended() {
	srand(time(NULL));

	if (GetModuleHandleA("codextended.dll") != NULL) {
		return;
	}

	if (!determine_cod_version()) {
		if (!find_cod_version()) {
			MsgBox("Failed to find Call of Duty version, please report this at www.cod1x.eu.");
			return;
		}
	}

#ifdef ENABLE_CODX
	if (!apply_hooks()) {
		MsgBox("Failed to initialize CoDExtended, please report this at www.cod1x.eu.\n");
		Com_Quit_f();
	}

#endif
}

void codextended_unload() {}

#include "shared.h"
#include "script.h"

int __declspec(naked) Scr_FarHook(int a1) {
#if 0
	int(*o)(int);
	if (codversion == COD_1)
		*(int*)&o = 0x46CEF0;
	else if (codversion == CODUO_51)
		*(int*)&o = GAME_OFF(0x20059510);//*(int*)&o = 0x47F9A0;

	int ret = o(a1);
	return ret;
#endif
	__asm xor eax, eax
	__asm ret
}


void Script_SetHook() {
#if 0
		__call(0x404A80, (int)Scr_FarHook);
		__call(0x457A6D, (int)Scr_FarHook);
		__call(0x457A82, (int)Scr_FarHook);
#endif
}
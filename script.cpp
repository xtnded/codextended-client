#include "shared.h"
#include "script.h"

SCR_FUNCS Scr;

#define UO_g_entities_ptr 0x20118D40
#define UO_g_entities_size 844

#pragma pack(push, 1)
typedef struct {
	char _stuff[352];
	int *client;
	char _filler[UO_g_entities_size - 352 - sizeof(int*)];
} uo_gentity_t;
#pragma pack(pop)

uo_gentity_t *uo_g_entities;


void PlayerCmd_GetPlayerAngles(int selfNum) {
	uo_gentity_t *self = &uo_g_entities[selfNum];
	if (!self->client) {
		Scr.AddUndefined();
		return;
	}
	float *angles = (float*)((int)self->client + 232);
	Scr.AddVector(angles);

}

void lolm8(int self) {
	//char *str = Scr.GetString(0);

	Scr.MakeArray();

	Scr.AddInt(2);
	Scr.AddArray();
}

SCRIPTFUNCTION scriptMethods[] = {
	//name, function, developer

	{ "getplayerangles", PlayerCmd_GetPlayerAngles, 0 },
	{ NULL, 0, 0 }
};
/* removed mysql close and connect/init it's too low ish */
SCRIPTFUNCTION scriptFunctions[] = {
#ifdef uMYSQL
	//MYSQL
	//{ "mysql_init", GScr_mysql_init, 0 },
	//{ "mysql_close", GScr_mysql_close, 0 },
	{ "mysql_affected_rows", GScr_mysql_affected_rows, 0 },
	{ "mysql_errno", GScr_mysql_errno, 0 },
	{ "mysql_error", GScr_mysql_error, 0 },
	{ "mysql_fetch_field", GScr_mysql_fetch_field, 0 },
	{ "mysql_fetch_row", GScr_mysql_fetch_row, 0 },
	{ "mysql_field_seek", GScr_mysql_field_seek, 0 },
	{ "mysql_free_result", GScr_mysql_free_result, 0 },
	{ "mysql_num_fields", GScr_mysql_num_fields, 0 },
	{ "mysql_num_rows", GScr_mysql_num_rows, 0 },
	{ "mysql_query", GScr_mysql_query, 0 },
	//{ "mysql_real_connect", GScr_mysql_real_connect, 0 },
	{ "mysql_real_escape_string", GScr_mysql_real_escape_string, 0 },
	{ "mysql_store_result", GScr_mysql_store_result, 0 },
	{ "mysql_get_connection", GScr_mysql_get_connection, 0 },
	{ "xmysql_connect", GScr_mysql_connect_global, 0 },
	//MYSQL END
#endif
	{ "php_test", lolm8, 0 },
	{ NULL, 0, 0 }
};

SCRIPTFUNCTIONCALL Scr_GetCustomMethod(const char** fname, int* fdev) {
	SCRIPTFUNCTIONCALL(*getmethod)(const char**, int*);
	*(int*)&getmethod = *(int*)0x9D65F8;


	SCRIPTFUNCTIONCALL ret = getmethod(fname, fdev);

	if (!ret) {
		for (unsigned int i = 0; scriptMethods[i].name; i++) {
			if (!strcmp(*fname, scriptMethods[i].name)) {
				SCRIPTFUNCTION func = scriptMethods[i];
				*fname = func.name;
				*fdev = func.developer;
				return func.call;
			}
		}
	}
	return ret;
}

SCRIPTFUNCTIONCALL Scr_GetCustomFunction(const char** fname, int* fdev) {
	SCRIPTFUNCTIONCALL(*getfunc)(const char**, int*);
	*(int*)&getfunc = *(int*)0x9D65F4;


	SCRIPTFUNCTIONCALL ret = getfunc(fname, fdev);

	if (!ret) {
		for (unsigned int i = 0; scriptFunctions[i].name; i++) {
			if (!strcmp(*fname, scriptFunctions[i].name)) {
				SCRIPTFUNCTION func = scriptFunctions[i];
				*fname = func.name;
				*fdev = func.developer;
				return func.call;
			}
		}
	}
	return ret;
}

void Scr_SetFuncs() {

	int *scr_funcs = NULL;

	if (codversion == COD_1)
		scr_funcs = (int*)0x8E5F18;
	else if (codversion == CODUO_51)
		scr_funcs = (int*)0x9D6608;

	for (int i = 0; i < (sizeof(SCR_FUNCS) / 4); i++) {
#if 0
		if (scr_funcs[i] == 0x00490960)
			MsgBox(va("i = %d, str =%s, addarray", i, scr_funcs_names[i]));
		else if (scr_funcs[i] == 0x00490910)
			MsgBox(va("i=%d, str = %s, makearray", i,scr_funcs_names[i]));
#endif
		*(int*)((int)&Scr.GetBool + i * 4) = scr_funcs[i];
	}


	//MsgBox(va("Scr.MakeArray = %x\nScr.AddArray=%x\n", Scr.MakeArray, Scr.AddArray));
}

void GScr_LoadGameTypeScript() {
	void(*o)();

	if (codversion == CODUO_51)
		*(int*)&o = GAME_OFF(0x200361B0);

	Scr_SetFuncs();

	o();
}

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
	if (codversion == COD_1) {
#if 0
		__call(0x404A80, (int)Scr_FarHook);
		__call(0x457A6D, (int)Scr_FarHook);
		__call(0x457A82, (int)Scr_FarHook);
#endif
	} else if (codversion == CODUO_51) {

		//Scr.AddVector = (void(*)(float*))0x4908C0;
#if 0
		__call(0x4053EB, (int)Scr_FarHook);
		__call(0x45EB5D, (int)Scr_FarHook);
		__call(0x45EB72, (int)Scr_FarHook);
#endif

		__call(GAME_OFF(0x20036526), (int)GScr_LoadGameTypeScript);
		uo_g_entities = (uo_gentity_t*)GAME_OFF(UO_g_entities_ptr);

		//__call(GAME_OFF(0x2002AC30), (int)Scr_FarHook);
		__call6to5(0x47C14E, (int)Scr_GetCustomMethod);
		__call6to5(0x47BEBE, (int)Scr_GetCustomFunction);
	}
}
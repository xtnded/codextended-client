#include "shared.h"

Cvar_Get_t Cvar_Get = (Cvar_Get_t)0x439350;
Cvar_Set_t Cvar_Set = (Cvar_Set_t)0x439650;
Cvar_FindVar_t Cvar_FindVar = (Cvar_FindVar_t)0x439280;

float Cvar_VariableValue(const char *var_name) {
	cvar_t  *var;

	var = Cvar_FindVar(var_name);
	if (!var) {
		return 0;
	}
	return var->value;
}

int Cvar_VariableIntegerValue(const char *var_name) {
	cvar_t  *var;

	var = Cvar_FindVar(var_name);
	if (!var) {
		return 0;
	}
	return var->integer;
}

char *Cvar_VariableString(const char *var_name) {
	cvar_t *var;

	var = Cvar_FindVar(var_name);
	if (!var) {
		return "";
	}
	return var->string;
}

char* Cvar_VariableStringBuffer(const char *var_name, char *buffer, int bufsize) {
	cvar_t *var;

	var = Cvar_FindVar(var_name);
	if (!var) {
		*buffer = 0;
	} else {
		Q_strncpyz(buffer, var->string, bufsize);
	}
	return buffer;
}

void Cvar_LatchedVariableStringBuffer(const char *var_name, char *buffer, int bufsize) {
	cvar_t *var;

	var = Cvar_FindVar(var_name);
	if (!var) {
		*buffer = 0;
	} else {
		if (var->latchedString) {
			Q_strncpyz(buffer, var->latchedString, bufsize);
		} else {
			Q_strncpyz(buffer, var->string, bufsize);
		}
	}
}

#include "shared.h"

char *trimSpaces(char *str) {
	char *end;

	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0) return str;

	end = str + strlen(str) - 1;

	while (end > str && isspace((unsigned char)*end))
		end--;

	end[1] = '\0';

	return str;
}

char* __cdecl CL_ClearHostname(char* a1, char* a2, size_t a3) {
	//Remove spaces 
	a2 = trimSpaces(a2);

	// remove symbols
	char nosymbols[128];
	int i = 0, c = 0;
	for (; i < strlen(a2); i++) {
		// if (isalnum(a2[i])) {
		if ((a2[i] >= 0x20 && a2[i] <= 0x7E)) {
			nosymbols[c] = a2[i];
			c++;
		}
	}
	nosymbols[c] = '\0';

	//Fix unnamed servers
	if (strlen(nosymbols) == 0)
		strncpy(nosymbols, "Unnamed Server", sizeof(nosymbols));

	return strncpy(a1, nosymbols, a3);
}
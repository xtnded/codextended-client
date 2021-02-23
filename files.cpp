#include "shared.h"

FS_CreatePath_t FS_CreatePath = (FS_CreatePath_t)0x429000;
FS_ComparePaks_t FS_ComparePaks = (FS_ComparePaks_t)0x43B830;

FS_ReadFile_t FS_ReadFile = (FS_ReadFile_t)0x42A8B0;
FS_FreeFile_t FS_FreeFile = (FS_FreeFile_t)0x42AB50;

#define PATH_SEP '/'

static void FS_ReplaceSeparators(char *path) {
	char    *s;

	for (s = path; *s; s++) {
		if (*s == '/' || *s == '\\') {
			*s = PATH_SEP;
		}
	}
}

char *FS_BuildOSPath(const char *base, const char *game, const char *qpath) {
	char temp[MAX_OSPATH];
	static char ospath[2][MAX_OSPATH];
	static int toggle;

	toggle ^= 1;        // flip-flop to allow two returns without clash

	if (!game || !game[0]) {
		game = (const char*)Cvar_VariableString("fs_game");
	}

	Com_sprintf(temp, sizeof(temp), "/%s/%s", game, qpath);
	FS_ReplaceSeparators(temp);
	Com_sprintf(ospath[toggle], sizeof(ospath[0]), "%s%s", base, temp);

	return ospath[toggle];
}

int FS_IsLegacyFile(const char* filename) {
	char *game = Cvar_VariableString("fs_game");
	if (game && *game)
		return 0;
	if (strstr(filename, "localized_"))
		return 1;
	for (int i = 0; i < 6; i++) {
		if (!strcmp(va("pak%d.pk3", i), filename))
			return 1;
	}
	return 0;
}
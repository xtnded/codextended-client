#include "shared.h"


/*
============================================================================

PARSING

============================================================================
*/

static char com_token[MAX_TOKEN_CHARS];
static char com_parsename[MAX_TOKEN_CHARS];
static int com_lines;

static int backup_lines;
static char    *backup_text;

void COM_BeginParseSession(const char *name) {
	com_lines = 0;
	Com_sprintf(com_parsename, sizeof(com_parsename), "%s", name);
}

void COM_BackupParseSession(char **data_p) {
	backup_lines = com_lines;
	backup_text = *data_p;
}

void COM_RestoreParseSession(char **data_p) {
	com_lines = backup_lines;
	*data_p = backup_text;
}

void COM_SetCurrentParseLine(int line) {
	com_lines = line;
}

int COM_GetCurrentParseLine(void) {
	return com_lines;
}

char *COM_ParseExt(char **data_p, qboolean allowLineBreaks);
char *COM_Parse(char **data_p) {
	return COM_ParseExt(data_p, qtrue);
}

void COM_ParseError(char *format, ...) {
	va_list argptr;
	static char string[4096];

	va_start(argptr, format);
	Q_vsnprintf(string, sizeof(string), format, argptr);
	va_end(argptr);

	Com_Printf("ERROR: %s, line %d: %s\n", com_parsename, com_lines, string);
}

void COM_ParseWarning(char *format, ...) {
	va_list argptr;
	static char string[4096];

	va_start(argptr, format);
	Q_vsnprintf(string, sizeof(string), format, argptr);
	va_end(argptr);

	Com_Printf("WARNING: %s, line %d: %s\n", com_parsename, com_lines, string);
}

/*
==============
COM_Parse

Parse a token out of a string
Will never return NULL, just empty strings

If "allowLineBreaks" is qtrue then an empty
string will be returned if the next token is
a newline.
==============
*/
static char *SkipWhitespace(char *data, qboolean *hasNewLines) {
	int c;

	while ((c = *data) <= ' ') {
		if (!c) {
			return NULL;
		}
		if (c == '\n') {
			com_lines++;
			*hasNewLines = qtrue;
		}
		data++;
	}

	return data;
}

int COM_Compress(char *data_p) {
	char *datai, *datao;
	int c, pc, size;
	qboolean ws = qfalse;

	size = 0;
	pc = 0;
	datai = datao = data_p;
	if (datai) {
		while ((c = *datai) != 0) {
			if (c == 13 || c == 10) {
				*datao = c;
				datao++;
				ws = qfalse;
				pc = c;
				datai++;
				size++;
				// skip double slash comments
			}
			else if (c == '/' && datai[1] == '/') {
				while (*datai && *datai != '\n') {
					datai++;
				}
				ws = qfalse;
				// skip /* */ comments
			}
			else if (c == '/' && datai[1] == '*') {
				datai += 2; // Arnout: skip over '/*'
				while (*datai && (*datai != '*' || datai[1] != '/'))
				{
					datai++;
				}
				if (*datai) {
					datai += 2;
				}
				ws = qfalse;
			}
			else {
				if (ws) {
					*datao = ' ';
					datao++;
				}
				*datao = c;
				datao++;
				datai++;
				ws = qfalse;
				pc = c;
				size++;
			}
		}
	}
	*datao = 0;
	return size;
}

char *COM_ParseExt(char **data_p, qboolean allowLineBreaks) {
	int c = 0, len;
	qboolean hasNewLines = qfalse;
	char *data;

	data = *data_p;
	len = 0;
	com_token[0] = 0;

	// make sure incoming data is valid
	if (!data) {
		*data_p = NULL;
		return com_token;
	}

	// RF, backup the session data so we can unget easily
	COM_BackupParseSession(data_p);

	while (1)
	{
		// skip whitespace
		data = SkipWhitespace(data, &hasNewLines);
		if (!data) {
			*data_p = NULL;
			return com_token;
		}
		if (hasNewLines && !allowLineBreaks) {
			*data_p = data;
			return com_token;
		}

		c = *data;

		// skip double slash comments
		if (c == '/' && data[1] == '/') {
			data += 2;
			while (*data && *data != '\n') {
				data++;
			}
			//			com_lines++;
		}
		// skip /* */ comments
		else if (c == '/' && data[1] == '*') {
			data += 2;
			while (*data && (*data != '*' || data[1] != '/'))
			{
				data++;
				if (*data == '\n') {
					//					com_lines++;
				}
			}
			if (*data) {
				data += 2;
			}
		}
		else
		{
			break;
		}
	}

	// handle quoted strings
	if (c == '\"') {
		data++;
		while (1)
		{
			c = *data++;
			if (c == '\\' && *(data) == '\"') {
				// Arnout: string-in-string
				if (len < MAX_TOKEN_CHARS) {
					com_token[len] = '\"';
					len++;
				}
				data++;

				while (1) {
					c = *data++;

					if (!c) {
						com_token[len] = 0;
						*data_p = (char *)data;
						break;
					}
					if ((c == '\\' && *(data) == '\"')) {
						if (len < MAX_TOKEN_CHARS) {
							com_token[len] = '\"';
							len++;
						}
						data++;
						c = *data++;
						break;
					}
					if (len < MAX_TOKEN_CHARS) {
						com_token[len] = c;
						len++;
					}
				}
			}
			if (c == '\"' || !c) {
				com_token[len] = 0;
				*data_p = (char *)data;
				return com_token;
			}
			if (len < MAX_TOKEN_CHARS) {
				com_token[len] = c;
				len++;
			}
		}
	}

	// parse a regular word
	do
	{
		if (len < MAX_TOKEN_CHARS) {
			com_token[len] = c;
			len++;
		}
		data++;
		c = *data;
		if (c == '\n') {
			com_lines++;
		}
	} while (c > 32);

	if (len == MAX_TOKEN_CHARS) {
		//		Com_Printf ("Token exceeded %i chars, discarded.\n", MAX_TOKEN_CHARS);
		len = 0;
	}
	com_token[len] = 0;

	*data_p = (char *)data;
	return com_token;
}




/*
==================
COM_MatchToken
==================
*/
void COM_MatchToken(char **buf_p, char *match) {
	char    *token;

	token = COM_Parse(buf_p);
	if (strcmp(token, match)) {
		Com_Error(ERR_DROP, "MatchToken: %s != %s", token, match);
	}
}

/*
=================
SkipBracedSection_Depth

=================
*/
void SkipBracedSection_Depth(char **program, int depth) {
	char            *token;

	do {
		token = COM_ParseExt(program, qtrue);
		if (token[1] == 0) {
			if (token[0] == '{') {
				depth++;
			}
			else if (token[0] == '}')     {
				depth--;
			}
		}
	} while (depth && *program);
}

/*
=================
SkipBracedSection

The next token should be an open brace.
Skips until a matching close brace is found.
Internal brace depths are properly skipped.
=================
*/
void SkipBracedSection(char **program) {
	char            *token;
	int depth;

	depth = 0;
	do {
		token = COM_ParseExt(program, qtrue);
		if (token[1] == 0) {
			if (token[0] == '{') {
				depth++;
			}
			else if (token[0] == '}')     {
				depth--;
			}
		}
	} while (depth && *program);
}

/*
=================
SkipRestOfLine
=================
*/
void SkipRestOfLine(char **data) {
	char    *p;
	int c;

	p = *data;
	while ((c = *p++) != 0) {
		if (c == '\n') {
			com_lines++;
			break;
		}
	}

	*data = p;
}


void Parse1DMatrix(char **buf_p, int x, float *m) {
	char    *token;
	int i;

	COM_MatchToken(buf_p, "(");

	for (i = 0; i < x; i++) {
		token = COM_Parse(buf_p);
		m[i] = atof(token);
	}

	COM_MatchToken(buf_p, ")");
}

void Parse2DMatrix(char **buf_p, int y, int x, float *m) {
	int i;

	COM_MatchToken(buf_p, "(");

	for (i = 0; i < y; i++) {
		Parse1DMatrix(buf_p, x, m + i * x);
	}

	COM_MatchToken(buf_p, ")");
}

void Parse3DMatrix(char **buf_p, int z, int y, int x, float *m) {
	int i;

	COM_MatchToken(buf_p, "(");

	for (i = 0; i < z; i++) {
		Parse2DMatrix(buf_p, y, x, m + i * x * y);
	}

	COM_MatchToken(buf_p, ")");
}


/*
===============
Com_ParseInfos
===============
*/
int Com_ParseInfos(char *buf, int max, char infos[][MAX_INFO_STRING]) {
	const char  *token;
	int count;
	char key[MAX_TOKEN_CHARS];

	count = 0;

	while (1) {
		token = COM_Parse(&buf);
		if (!token[0]) {
			break;
		}
		if (strcmp(token, "{")) {
			Com_Printf("Missing { in info file\n");
			break;
		}

		if (count == max) {
			Com_Printf("Max infos exceeded\n");
			break;
		}

		infos[count][0] = 0;
		while (1) {
			token = COM_Parse(&buf);
			if (!token[0]) {
				Com_Printf("Unexpected end of info file\n");
				break;
			}
			if (!strcmp(token, "}")) {
				break;
			}
			Q_strncpyz(key, token, sizeof(key));

			token = COM_ParseExt(&buf, qfalse);
			if (!token[0]) {
				token = "<NULL>";
			}
			Info_SetValueForKey(infos[count], key, token);
		}
		count++;
	}

	return count;
}

void Q_strncpyz(char *dest, const char *src, int destsize) {
	if (!src) {
		Com_Error(ERR_FATAL, "Q_strncpyz: NULL src");
	}
	if (destsize < 1) {
		Com_Error(ERR_FATAL, "Q_strncpyz: destsize < 1");
	}

	strncpy(dest, src, destsize - 1);
	dest[destsize - 1] = 0;
}


int Q_stricmpn(const char *s1, const char *s2, int n) {
	int c1, c2;

	do {
		c1 = *s1++;
		c2 = *s2++;

		if (!n--) {
			return 0;       // strings are equal until end point
		}

		if (c1 != c2) {
			if (c1 >= 'a' && c1 <= 'z') {
				c1 -= ('a' - 'A');
			}
			if (c2 >= 'a' && c2 <= 'z') {
				c2 -= ('a' - 'A');
			}
			if (c1 != c2) {
				return c1 < c2 ? -1 : 1;
			}
		}
	} while (c1);

	return 0;       // strings are equal
}

int Q_strncmp(const char *s1, const char *s2, int n) {
	int c1, c2;

	do {
		c1 = *s1++;
		c2 = *s2++;

		if (!n--) {
			return 0;       // strings are equal until end point
		}

		if (c1 != c2) {
			return c1 < c2 ? -1 : 1;
		}
	} while (c1);

	return 0;       // strings are equal
}

int Q_stricmp(const char *s1, const char *s2) {
	return (s1 && s2) ? Q_stricmpn(s1, s2, 99999) : -1;
}

void Q_strcat(char *dest, int size, const char *src) {
	int l1;

	l1 = strlen(dest);
	if (l1 >= size) {
		Com_Error(ERR_FATAL, "Q_strcat: already overflowed");
	}
	Q_strncpyz(dest + l1, src, size - l1);
}

void QDECL Com_sprintf(char *dest, int size, const char *fmt, ...) {
	int ret;
	va_list argptr;

	va_start(argptr, fmt);
	ret = vsnprintf(dest, size, fmt, argptr);
	va_end(argptr);
	if (ret == -1) {
		Com_Printf("Com_sprintf: overflow of %i bytes buffer\n", size);
	}
}

int Cmd_Argc() {
	return *(int*)0x8930F0;
}

char** cmd_argv = (char**)0x890BF0;

char* Cmd_Argv(int index) {
	if (index >= Cmd_Argc())
		return "";
	return cmd_argv[index];
}


/*
=====================================================================

INFO STRINGS

=====================================================================
*/

/*
===============
Info_ValueForKey

Searches the string for the given
key and returns the associated value, or an empty string.
FIXME: overflow check?
===============
*/
char *Info_ValueForKey(const char *s, const char *key) {
	char pkey[BIG_INFO_KEY];
	static char value[2][BIG_INFO_VALUE];   // use two buffers so compares
	// work without stomping on each other
	static int valueindex = 0;
	char    *o;

	if (!s || !key) {
		return "";
	}

	if (strlen(s) >= BIG_INFO_STRING) {
		Com_Error(ERR_DROP, "Info_ValueForKey: oversize infostring [%s] [%s]", s, key);
	}

	valueindex ^= 1;
	if (*s == '\\') {
		s++;
	}
	while (1)
	{
		o = pkey;
		while (*s != '\\')
		{
			if (!*s) {
				return "";
			}
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value[valueindex];

		while (*s != '\\' && *s)
		{
			*o++ = *s++;
		}
		*o = 0;

		if (!Q_stricmp(key, pkey)) {
			return value[valueindex];
		}

		if (!*s) {
			break;
		}
		s++;
	}

	return "";
}


/*
===================
Info_NextPair

Used to itterate through all the key/value pairs in an info string
===================
*/
void Info_NextPair(const char **head, char *key, char *value) {
	char    *o;
	const char  *s;

	s = *head;

	if (*s == '\\') {
		s++;
	}
	key[0] = 0;
	value[0] = 0;

	o = key;
	while (*s != '\\') {
		if (!*s) {
			*o = 0;
			*head = s;
			return;
		}
		*o++ = *s++;
	}
	*o = 0;
	s++;

	o = value;
	while (*s != '\\' && *s) {
		*o++ = *s++;
	}
	*o = 0;

	*head = s;
}


/*
===================
Info_RemoveKey
===================
*/
void Info_RemoveKey(char *s, const char *key) {
	char    *start;
	char pkey[MAX_INFO_KEY];
	char value[MAX_INFO_VALUE];
	char    *o;

	if (strlen(s) >= MAX_INFO_STRING) {
		Com_Error(ERR_DROP, "Info_RemoveKey: oversize infostring [%s] [%s]", s, key);
	}

	if (strchr(key, '\\')) {
		return;
	}

	while (1)
	{
		start = s;
		if (*s == '\\') {
			s++;
		}
		o = pkey;
		while (*s != '\\')
		{
			if (!*s) {
				return;
			}
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value;
		while (*s != '\\' && *s)
		{
			if (!*s) {
				return;
			}
			*o++ = *s++;
		}
		*o = 0;

		if (!Q_stricmp(key, pkey)) {
			// rain - arguments to strcpy must not overlap
			//strcpy (start, s);	// remove this part
			memmove(start, s, strlen(s) + 1); // remove this part
			return;
		}

		if (!*s) {
			return;
		}
	}

}

/*
===================
Info_RemoveKey_Big
===================
*/
void Info_RemoveKey_Big(char *s, const char *key) {
	char    *start;
	char pkey[BIG_INFO_KEY];
	char value[BIG_INFO_VALUE];
	char    *o;

	if (strlen(s) >= BIG_INFO_STRING) {
		Com_Error(ERR_DROP, "Info_RemoveKey_Big: oversize infostring [%s] [%s]", s, key);
	}

	if (strchr(key, '\\')) {
		return;
	}

	while (1)
	{
		start = s;
		if (*s == '\\') {
			s++;
		}
		o = pkey;
		while (*s != '\\')
		{
			if (!*s) {
				return;
			}
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value;
		while (*s != '\\' && *s)
		{
			if (!*s) {
				return;
			}
			*o++ = *s++;
		}
		*o = 0;

		if (!Q_stricmp(key, pkey)) {
			strcpy(start, s);  // remove this part
			return;
		}

		if (!*s) {
			return;
		}
	}

}




/*
==================
Info_Validate

Some characters are illegal in info strings because they
can mess up the server's parsing
==================
*/
qboolean Info_Validate(const char *s) {
	if (strchr(s, '\"')) {
		return qfalse;
	}
	if (strchr(s, ';')) {
		return qfalse;
	}
	return qtrue;
}

/*
==================
Info_SetValueForKey

Changes or adds a key/value pair
==================
*/
void Info_SetValueForKey(char *s, const char *key, const char *value) {
	char newi[MAX_INFO_STRING];

	if (strlen(s) >= MAX_INFO_STRING) {
		Com_Error(ERR_DROP, "Info_SetValueForKey: oversize infostring [%s] [%s] [%s]", s, key, value);
	}

	if (strchr(key, '\\') || strchr(value, '\\')) {
		Com_Printf("Can't use keys or values with a \\\n");
		return;
	}

	if (strchr(key, ';') || strchr(value, ';')) {
		Com_Printf("Can't use keys or values with a semicolon\n");
		return;
	}

	if (strchr(key, '\"') || strchr(value, '\"')) {
		Com_Printf("Can't use keys or values with a \"\n");
		return;
	}

	Info_RemoveKey(s, key);
	if (!value || !strlen(value)) {
		return;
	}

	Com_sprintf(newi, sizeof(newi), "\\%s\\%s", key, value);

	if (strlen(newi) + strlen(s) > 0x17f) {
		Com_Printf("Info string length exceeded\n");
		return;
	}

	strcat(s, newi);
}

/*
==================
Info_SetValueForKey_Big

Changes or adds a key/value pair
==================
*/
void Info_SetValueForKey_Big(char *s, const char *key, const char *value) {
	char newi[BIG_INFO_STRING];

	if (strlen(s) >= BIG_INFO_STRING) {
		Com_Error(ERR_DROP, "Info_SetValueForKey: oversize infostring [%s] [%s] [%s]", s, key, value);
	}

	if (strchr(key, '\\') || strchr(value, '\\')) {
		Com_Printf("Can't use keys or values with a \\\n");
		return;
	}

	if (strchr(key, ';') || strchr(value, ';')) {
		Com_Printf("Can't use keys or values with a semicolon\n");
		return;
	}

	if (strchr(key, '\"') || strchr(value, '\"')) {
		Com_Printf("Can't use keys or values with a \"\n");
		return;
	}

	Info_RemoveKey_Big(s, key);
	if (!value || !strlen(value)) {
		return;
	}

	Com_sprintf(newi, sizeof(newi), "\\%s\\%s", key, value);

	if (strlen(newi) + strlen(s) > BIG_INFO_STRING) {
		Com_Printf("BIG Info string length exceeded\n");
		return;
	}

	strcat(s, newi);
}

char* trimSpaces(char* str) {
	char* end;

	while (isspace((unsigned char)*str))
		str++;

	if (*str == 0) return str;

	end = str + strlen(str) - 1;

	while (end > str && isspace((unsigned char)*end))
		end--;

	end[1] = '\0';

	return str;
}

char* Q_CleanStr(char* string, bool colors) {
	char* d;
	char* s;
	int c;

	s = string;
	d = string;
	while ((c = *s) != 0) {
		if (Q_IsColorString(s) && !colors) {
			s++;
		}
		else if (c >= 0x20 && c <= 0x7E) {
			*d++ = c;
		}
		s++;
	}
	*d = '\0';

	return string;
}
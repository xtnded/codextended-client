#include "shared.h"

#define MAX_GLOBAL_SERVERS 2048
#define MAX_OTHER_SERVERS 128

struct rest;

typedef struct {
	netadr_t adr;
	char hostName[MAX_NAME_LENGTH];
	struct rest;
} serverInfo_t; //size = 0xB8

struct rest {
	char _rest[0xB8 - sizeof(serverInfo_t)];
};

static char *CleanStr(char *string) {
	char*   d;
	char*   s;
	int c;

	s = string;
	d = string;
	while ((c = *s) != 0) {
		/*if ( Q_IsColorString( s ) ) {
		s++;
		} else */if (c >= 0x20 && c <= 0x7E)   {
			*d++ = c;
		}
	s++;
	}
	*d = '\0';

	return string;
}

typedef enum {
	AS_LOCAL,
	AS_GLOBAL,
	AS_FAVORITES
} server_connection_source_type;

static int a1, a2, a3, a4;

static void(*setserverinfo_jmp)() = (void(*)())0x417A10;

__declspec(naked) void CL_SetServerInfo() {
	__asm
	{
		push eax
			mov eax, dword ptr ss : [esp + 0xc]
			mov a1, eax //server index
			mov eax, dword ptr ss : [esp + 8]
			mov a2, eax //a4
			pop eax
	}
	//Com_Printf("server idx = %d, a4=%d\n", a1,a2);
	__asm jmp setserverinfo_jmp
}

static int max;

int server = 0;
char *hostName = NULL;

__declspec(naked) void cl_setserverinfo_end() {
	hostName = NULL;
	max = (a2 == AS_GLOBAL) ? MAX_GLOBAL_SERVERS : MAX_OTHER_SERVERS;

	if (a1 < 0 || a1 > max)
		goto end_proc;

	server = (0x155F404 + 184 * a1); //local

	if (a2) {
		if (a2 == 1)
			server = (0x1565008 + 184 * a1);
		else if (a2 == 2)
			server = (0x15C4010 + 184 * a1);
	}

	hostName = (char*)(server + 20);
	if (hostName) {
		CleanStr(hostName);
		//Com_Printf("hostname = %s\n", hostName);

	}

end_proc:
	__asm retn
	/*
	__asm
	{
	mov eax, 0x52E7B9
	jmp eax
	}
	*/
}
const char  *NET_AdrToString(netadr_t a);

void LAN_LoadCachedServers() {
	void(*o)() = (void(*)())0x417490;

	o();

#if 0
	FILE *fp = fopen("servers.txt", "w");
	if (!fp)
		return;

	serverInfo_t *list = (serverInfo_t*)0x1565008, *cur = NULL;
	int num = *(int*)0x1565004;

	for (int i = 0; i < num; i++) {
		cur = (serverInfo_t*)((int)list + 0xb8 * i);
		fprintf(fp, "%s: %s\n", NET_AdrToString(cur->adr), cur->hostName);
	}
	fclose(fp);
#endif
}
#include "shared.h"
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <wsipx.h>
#include "exmaster_client.h"
#include "client.h"

Sys_SendPacket_t Sys_SendPackett = (Sys_SendPacket_t)0x464AA0;
NET_SendPacket_t NET_SendPacket = (NET_SendPacket_t)0x4493E0;

NET_OutOfBandPrint_t NET_OutOfBandPrint = (NET_OutOfBandPrint_t)0x449490;

CL_Netchan_Encode_t CL_Netchan_Encode = (CL_Netchan_Encode_t)0x414710;
Netchan_Transmit_t Netchan_Transmit = (Netchan_Transmit_t)0x448B70;
Netchan_TransmitNextFragment_t Netchan_TransmitNextFragment = (Netchan_TransmitNextFragment_t)0x448980;

MSG_initHuffman_t MSG_initHuffman = (MSG_initHuffman_t)0x448390;

void MSG_Init(msg_t *buf, byte *data, int length) {
	if (!*(int*)0x14073F0)
		MSG_initHuffman();
	memset(buf, 0, sizeof(*buf));
	buf->data = data;
	buf->maxsize = length;
}

#define DO( src,dest )	  \
	copy[0] = s[src];	\
	copy[1] = s[src + 1];	\
	sscanf( copy, "%x", &val );	  \
	( (struct sockaddr_ipx *)sadr )->dest = val

qboolean Sys_StringToSockaddr(const char *s, struct sockaddr *sadr) {
	struct hostent  *h;
	int val;
	char copy[MAX_STRING_CHARS];

	memset(sadr, 0, sizeof(*sadr));

	// check for an IPX address
	// rain - too easy to falsely match a real hostname
	//	if( ( strlen( s ) == 21 ) && ( s[8] == '.' ) ) {
	((struct sockaddr_in *)sadr)->sin_family = AF_INET;
	((struct sockaddr_in *)sadr)->sin_port = 0;

	if (s[0] >= '0' && s[0] <= '9') {
		*(int *)&((struct sockaddr_in *)sadr)->sin_addr = inet_addr(s);
	}
	else {
		if ((h = gethostbyname(s)) == 0) {
			return qfalse;
		}
		*(int *)&((struct sockaddr_in *)sadr)->sin_addr = *(int *)h->h_addr_list[0];
	}

	return qtrue;
}

#undef DO


void SockadrToNetadr(struct sockaddr *s, netadr_t *a) {
	a->type = NA_IP;
	*(int *)&a->ip = ((struct sockaddr_in *)s)->sin_addr.s_addr;
	a->port = ((struct sockaddr_in *)s)->sin_port;
}

void NetadrToSockadr(netadr_t *a, struct sockaddr *s) {
	memset(s, 0, sizeof(*s));

	if (a->type == NA_BROADCAST) {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_port = a->port;
		((struct sockaddr_in *)s)->sin_addr.s_addr = INADDR_BROADCAST;
	}
	else if (a->type == NA_IP)    {
		((struct sockaddr_in *)s)->sin_family = AF_INET;
		((struct sockaddr_in *)s)->sin_addr.s_addr = *(int *)&a->ip;
		((struct sockaddr_in *)s)->sin_port = a->port;
	}
}

qboolean Sys_StringToAdr(const char *s, netadr_t *a) {
	struct sockaddr sadr;

	if (!Sys_StringToSockaddr(s, &sadr)) {
		return qfalse;
	}

	SockadrToNetadr(&sadr, a);
	return qtrue;
}

//tmp relocation
short   BigShort(short l) {
	byte b1, b2;

	b1 = l & 255;
	b2 = (l >> 8) & 255;

	return (b1 << 8) + b2;
}

qboolean    NET_StringToAdr(const char *s, netadr_t *a) {
	qboolean r;
	char base[MAX_STRING_CHARS];
	char    *port;

	if (!strcmp(s, "localhost")) {
		memset(a, 0, sizeof(*a));
		a->type = NA_LOOPBACK;
		return qtrue;
	}

	// look for a port number
	Q_strncpyz(base, s, sizeof(base));
	port = strstr(base, ":");
	if (port) {
		*port = 0;
		port++;
	}

	r = Sys_StringToAdr(base, a);

	if (!r) {
		a->type = NA_BAD;
		return qfalse;
	}

	// inet_addr returns this if out of range
	if (a->ip[0] == 255 && a->ip[1] == 255 && a->ip[2] == 255 && a->ip[3] == 255) {
		a->type = NA_BAD;
		return qfalse;
	}

	if (port) {
		a->port = BigShort((short)atoi(port));
	}
	else {
		a->port = BigShort(28960);
	}

	return qtrue;
}

const char  *NET_AdrToString(netadr_t a) {
	static  char    s[64];

	if (a.type == NA_LOOPBACK) {
		Com_sprintf(s, sizeof(s), "loopback");
	}
	else if (a.type == NA_BOT) {
		Com_sprintf(s, sizeof(s), "bot");
	}
	else if (a.type == NA_IP) {
		Com_sprintf(s, sizeof(s), "%i.%i.%i.%i:%hu",
			a.ip[0], a.ip[1], a.ip[2], a.ip[3], BigShort(a.port));
	}
	else {
		Com_sprintf(s, sizeof(s), "%02x%02x%02x%02x.%02x%02x%02x%02x%02x%02x:%hu",
			a.ipx[0], a.ipx[1], a.ipx[2], a.ipx[3], a.ipx[4], a.ipx[5], a.ipx[6], a.ipx[7], a.ipx[8], a.ipx[9],
			BigShort(a.port));
	}

	return s;
}

const char  *NET_BaseAdrToString(netadr_t a) {
	static  char    s[64];

	if (a.type == NA_LOOPBACK) {
		Com_sprintf(s, sizeof(s), "loopback");
	}
	else if (a.type == NA_BOT) {
		Com_sprintf(s, sizeof(s), "bot");
	}
	else if (a.type == NA_IP) {
		Com_sprintf(s, sizeof(s), "%i.%i.%i.%i",
			a.ip[0], a.ip[1], a.ip[2], a.ip[3]);
	}
	else {
		Com_sprintf(s, sizeof(s), "%02x%02x%02x%02x.%02x%02x%02x%02x%02x%02x",
			a.ipx[0], a.ipx[1], a.ipx[2], a.ipx[3], a.ipx[4], a.ipx[5], a.ipx[6], a.ipx[7], a.ipx[8], a.ipx[9]);
	}

	return s;
}

qboolean    NET_CompareAdr(netadr_t a, netadr_t b) {
	if (a.type != b.type) {
		return qfalse;
	}

	if (a.type == NA_LOOPBACK) {
		return qtrue;
	}

	if (a.type == NA_IP) {
		if (a.ip[0] == b.ip[0] && a.ip[1] == b.ip[1] && a.ip[2] == b.ip[2] && a.ip[3] == b.ip[3] && a.port == b.port) {
			return qtrue;
		}
		return qfalse;
	}

	if (a.type == NA_IPX) {
		if ((memcmp(a.ipx, b.ipx, 10) == 0) && a.port == b.port) {
			return qtrue;
		}
		return qfalse;
	}

	Com_Printf("NET_CompareAdr: bad address type\n");
	return qfalse;
}


bool    NET_IsLocalAddress(netadr_t adr) {
	return adr.type == NA_LOOPBACK;
}


qboolean    NET_CompareBaseAdr(netadr_t a, netadr_t b) {
	if (a.type != b.type) {
		return qfalse;
	}

	if (a.type == NA_LOOPBACK) {
		return qtrue;
	}

	if (a.type == NA_IP) {
		if (a.ip[0] == b.ip[0] && a.ip[1] == b.ip[1] && a.ip[2] == b.ip[2] && a.ip[3] == b.ip[3]) {
			return qtrue;
		}
		return qfalse;
	}

	if (a.type == NA_IPX) {
		if ((memcmp(a.ipx, b.ipx, 10) == 0)) {
			return qtrue;
		}
		return qfalse;
	}


	Com_Printf("NET_CompareBaseAdr: bad address type\n");
	return qfalse;
}

netadr_t ex_master;

bool ex_master_resolve() {
	static bool resolve_try = false;
	if (resolve_try)
		return true;
	if (!NET_StringToAdr(EX_MASTER_NAME, &ex_master)) {
		Com_Printf("^1Failed to resolve master '%s'\n", EX_MASTER_NAME);
		return false;
	}
	ex_master.port = BigShort(20511);
	resolve_try = true;
	return true;
}

void Sys_SendPacket(int packet_size, void *packet, netadr_t to) {
	__asm {
		/*
		sub     esp, 14h
		.text:00449465                 mov     ecx, 5
		.text:0044946A                 lea     esi, [esp+20h+arg_4]
		.text:0044946E                 mov     edi, esp
		.text:00449470                 rep movsd
		.text:00449472                 mov     ecx, ebp        ; buf
		.text:00449474                 mov     edx, ebx        ; len
		.text:00449476                 call    Sys_SendPacket
		.text:0044947B                 add     esp, 14h
		*/

		sub esp, 14h
		mov ecx, 5 // size of netadr_t is 20 / sizeof(32 bit register) = 5
		lea esi, [to]
		mov edi, esp
		rep movsd
		mov ecx, packet
		mov edx, packet_size
		call Sys_SendPackett
		add esp, 14h
	}
}

bool enc_connected = false;
#include "version_info.h"
#define EXT_NET_VERSION BUILDNUMBER
#define EXT_PACKET_TYPE 0xffff

typedef enum {
	ENC_NULL,
	ENC_VERIF,
	ENC_TALK,
	ENC_GET_KEY,
	ENC_SV_REQUEST_AUTH,
	ENC_HEARTBEAT,
	ENC_UPDATE_REQUEST,

	ENC_BROADCAST,
	ENC_CLIENT_JOINED,
	ENC_CLIENT_DISCONNECTED,
	ENC_FRIEND_REQUEST,
	ENC_CLIENT_USERINFO_CHANGED,
	ENC_END
} ext_net_cmd;

static char mUID[33] = { 0 };

static unsigned int ext_sv_enc_key = 0;
static unsigned int ext_cl_enc_key = 0;

static char ext_sv_enc_key_buf[11]{0};
static char ext_cl_enc_key_buf[11]{0};

static inline void xor_crypt(char *key, int key_len, char *buffer, int buf_len) {
	for (int i = 0; i < buf_len; i++)
		buffer[i] = buffer[i] ^ key[i % key_len];
}

#define sPrintf Com_Printf

void Enc_SendTalkMessage(const char *chatmsg) {

	rMSG msg;
	msg.AddInt(EXT_PACKET_TYPE);
	msg.AddByte(ENC_TALK);
	msg.AddString(chatmsg);
	msg.SendEnc(ex_master, ext_cl_enc_key_buf);
}

void Enc_SendFriendRequest() {
	char *var = Cvar_VariableString("cm_pl_selectedid");
	unsigned id = atoll(var);

	rMSG msg;
	msg.AddInt(EXT_PACKET_TYPE);
	msg.AddByte(ENC_FRIEND_REQUEST);
	msg.AddUInt(id);
	msg.SendEnc(ex_master, ext_cl_enc_key_buf);
}

bool bEncConnected = false;

void Enc_SendUserInfo() {
	if (!bEncConnected)
		return;

	rMSG reply;
	reply.AddInt(EXT_PACKET_TYPE);
	reply.AddByte(ENC_CLIENT_USERINFO_CHANGED);

	char _cs[MAX_STRING_CHARS] = { 0 };

	Info_SetValueForKey(_cs, "name", Cvar_VariableString("name"));
	Info_SetValueForKey(_cs, "message", "x");
	reply.AddString(_cs);
	reply.SendEnc(ex_master, ext_cl_enc_key_buf);
}

void Enc_SendHeartbeat() {
	if (!bEncConnected)
		return;

	extern cvar_t *clientname;

	if (clientname->modified) {
		Enc_SendUserInfo();
		clientname->modified = qfalse;
		return;
	}

	static time_t last = time(NULL);

	time_t now = time(NULL);
	if (difftime(now, last) < 5) {
		return;
	}
	
	int connectedToServer = 0;

	if (*cls_servername)
		connectedToServer = 1;

	rMSG msg;
	msg.AddInt(EXT_PACKET_TYPE);
	msg.AddByte(ENC_HEARTBEAT);
	msg.AddUInt(EXT_NET_VERSION);
	msg.AddInt(connectedToServer);
	if (connectedToServer)
		msg.AddString(cls_servername);
	msg.SendEnc(ex_master, ext_cl_enc_key_buf);
	last = time(NULL);
}

bool GetEncKey() {
	mClients.clear();

	rMSG msg;

	msg.AddInt(EXT_PACKET_TYPE);
	msg.AddByte(ENC_GET_KEY);
	msg.AddUInt(EXT_NET_VERSION);
	do {
		ext_cl_enc_key = ((rand() << 16) ^ rand()) ^ time(NULL);
	} while (!ext_cl_enc_key);
	Com_sprintf(ext_cl_enc_key_buf, sizeof(ext_cl_enc_key_buf), "%lu", ext_cl_enc_key);
	//sPrintf("cl enc key = %d\n", ext_cl_enc_key);
	msg.AddUInt(ext_cl_enc_key);
	msg.Send(ex_master);

	return true;
}

unsigned server_client_build = 0;

void ExtServer_Packet(netadr_t from, msg_t *mmsg) {
	void PH_Handle(netadr_t, char*, size_t);
	PH_Handle(from, (char*)mmsg->data, mmsg->cursize);

	return; //remove this for original functionality

	if (!NET_CompareBaseAdr(ex_master, from))
		return;
}

void NET_Init() {
	void(*o)();
	*(int*)&o = 0x465940;
	o();

	#if 0
	if (!ex_master_resolve())
		return;
	void PH_Init();
	PH_Init();
	#endif
}

static FARPROC cl_packetevent_ptr = (FARPROC)0x410FF0;

int clpe_pt = 0;

void __declspec(naked) CL_PacketEvent() {
	__asm {
			mov eax, [ecx + 0Ch]
			cmp eax, 4
			jl reg_cont
			mov eax, [ecx + 4]
			push eax
			mov eax, [eax]
			mov clpe_pt, eax
			pop eax
	}
	if (clpe_pt != -2) //-2
		goto c_reg_cont;
			/*
			cmp dword ptr[eax], 0FFFF0000h
			jnz reg_cont

			cmp dword ptr[eax], 0FFFFh
			jnz reg_cont
			*/
	__asm {
			push ecx
			sub esp, 14h
			mov ecx, 5
			//int 3
			lea esi, [esp + 01Ch]
			mov edi, esp
			rep movsd
			call ExtServer_Packet
			add esp, 18h
			retn
	}
	c_reg_cont:
	__asm {
		reg_cont :
			mov eax, 410FF0h
			jmp eax
	}
}

int __stdcall xrecvfrom(SOCKET s, char *buf, int len, int flags, sockaddr *from, int *fromlen) {
	int __stdcall ret = recvfrom(s, buf, len, flags, from, fromlen);
	return ret;
}

#define HTTP_PORT 80
#define BUFFERSIZE 8196

bool download_file(std::string url, char* filename) {
	std::string request;
	char buffer[BUFFERSIZE];
	struct sockaddr_in serveraddr;
	int sock;

	if (url.find("http://") != -1) {
		std::string temp = url;
		url = temp.substr(url.find("http://") + 7);
	}

	int dm = url.find("/");
	std::string file = url.substr(dm);
	std::string shost = url.substr(0, dm);

	request += "GET " + file + " HTTP/1.0\r\n";
	request += "Host: " + shost + "\r\n";
	request += "\r\n";

	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return FALSE;

	memset(&serveraddr, 0, sizeof(serveraddr));

	hostent *record = gethostbyname(shost.c_str());
	if (record == NULL)
		return FALSE;
	in_addr *address = (in_addr *)record->h_addr;
	std::string ipd = inet_ntoa(*address);
	const char *ipaddr = ipd.c_str();

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ipaddr);
	serveraddr.sin_port = htons(HTTP_PORT);

	if (connect(sock, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
		return FALSE;

	if (send(sock, request.c_str(), request.length(), 0) != request.length())
		return FALSE;

	int nRecv, npos;
	nRecv = recv(sock, (char*)&buffer, BUFFERSIZE, 0);
	std::string str_buff = buffer;
	npos = str_buff.find("\r\n\r\n");

	HANDLE hFile;
	hFile = CreateFileA(filename, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

	DWORD ss;
	while ((nRecv > 0) && (nRecv != INVALID_SOCKET)){
		if (npos > 0){
			char bf[BUFFERSIZE];
			// copy from end position of header //
			memcpy(bf, buffer + (npos + 4), nRecv - (npos + 4));
			WriteFile(hFile, bf, nRecv - (npos + 4), &ss, NULL);
		}
		else{
			// write normally if end not found //
			WriteFile(hFile, buffer, nRecv, &ss, NULL);
		}

		// buffer cleanup  //
		ZeroMemory(&buffer, sizeof(buffer));
		nRecv = recv(sock, (char*)&buffer, BUFFERSIZE, 0);
		str_buff = buffer;
		npos = str_buff.find("\r\n\r\n");
	}
	CloseHandle(hFile);
	closesocket(sock);
	return TRUE;
}
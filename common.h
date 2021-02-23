#pragma once

#include "stdafx.h"
#include <WinSock2.h>

#define MAX_MSGLEN              32768       // max length of a message, which may     

typedef enum {
	NA_BOT,
	NA_BAD,                 // an address lookup failed
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef struct {
	netadrtype_t type;
	union {
		int _ip;
		unsigned char ip[4];
	};
	unsigned char ipx[10];

	unsigned short port;
} netadr_t;

typedef enum {
	ERR_FATAL,                  // exit the entire game with a popup window
	//ERR_VID_FATAL,              // exit the entire game with a popup window and doesn't delete profile.pid
	ERR_DROP,                   // print to console and disconnect from game
	ERR_SERVERDISCONNECT,       // don't kill server
	ERR_DISCONNECT,             // client disconnected from the server
	ERR_NEED_CD,                // pop up the need-cd dialog
	ERR_AUTOUPDATE
} errorParm_t;

typedef void(*Com_Printf_t)(const char*, ...);
extern Com_Printf_t Com_Printf;

typedef void(*Com_DPrintf_t)(const char *, ...);
extern Com_DPrintf_t Com_DPrintf;

typedef void(*Com_Error_t)(int, const char*, ...);
extern Com_Error_t Com_Error;

typedef void(*xfunc)(void);

typedef void(*Cmd_AddCommand_t)(const char*, xfunc);
typedef void(*Cmd_RemoveCommand_t)(const char*);
extern Cmd_AddCommand_t Cmd_AddCommand;
extern Cmd_RemoveCommand_t Cmd_RemoveCommand;

typedef int(*FS_CreatePath_t)(const char *OSPath);
extern FS_CreatePath_t FS_CreatePath;

typedef int (*FS_ComparePaks_t)(char *neededpaks, int len, int dlstring);
extern FS_ComparePaks_t FS_ComparePaks;

typedef int(*FS_ReadFile_t)(const char *qpath, void **buffer);
extern FS_ReadFile_t FS_ReadFile;
typedef void(*FS_FreeFile_t)(void *);
extern FS_FreeFile_t FS_FreeFile;

char *FS_BuildOSPath(const char *base, const char *game, const char *qpath);

char * va(char *format, ...);

int Q_vsnprintf(char *dest, int size, const char *fmt, va_list argptr);
void Sys_SendPacket(int packet_size, void *packet, netadr_t to);
class rMSG {
public:
	bool oob;
	char buffer[MAX_MSGLEN];
	int bufsize;
	int readsize;

	rMSG(bool oob = false) : bufsize(0) {
		memset(buffer, 0, sizeof(buffer));
		this->oob = oob;
		if (oob)
			AddInt(-1);
		readsize = 0;
	}

	rMSG(char *buf, int len) {
		memset(buffer, 0, sizeof(buffer));
		int l = len > sizeof(buffer) ? sizeof(buffer) : len;
		memcpy(buffer, buf, l);
		bufsize = l;
		readsize = 0;
	}

	unsigned char ReadByte() {
		if (readsize + 1 > bufsize)
			return 0;
		return *(unsigned char*)(buffer + readsize++);
	}

	int ReadInt() {
		if (readsize + sizeof(int) > bufsize)
			return 0;
		readsize += sizeof(int);
		return ntohl(*(int*)(buffer + readsize - sizeof(int)));
	}

	void* ReadData(char *to, int len) {
		if (readsize + len > bufsize)
			return NULL;
		memcpy(to, buffer + readsize, len);
		readsize += len;
		return to;
	}

	short ReadShort() {
		if (readsize + sizeof(short) > bufsize)
			return 0;
		readsize += sizeof(short);
		return ntohs(*(short*)(buffer + readsize - sizeof(short)));
	}

	unsigned short ReadUShort() {
		if (readsize + sizeof(unsigned short) > bufsize)
			return 0;
		readsize += sizeof(unsigned short);
		return ntohs(*(unsigned short*)(buffer + readsize - sizeof(unsigned short)));
	}

	unsigned int ReadUInt() {
		if (readsize + sizeof(unsigned int) > bufsize)
			return 0;
		readsize += sizeof(unsigned int);
		return ntohl(*(unsigned int*)(buffer + readsize - sizeof(unsigned int)));
	}

	template <typename T>
	T ReadPrimitive() {
		if (readsize + sizeof(T) > bufsize)
			return 0;
		readsize += sizeof(T);
		return *(T*)(buffer + readsize - sizeof(T));
	}

	template <typename T>
	void AddPrimitive(T tee) {
		if (bufsize + sizeof(T) >= MAX_MSGLEN)
			return;
		*(T*)(buffer + bufsize) = tee;
		bufsize += sizeof(T);
	}

	void AddByte(unsigned char b) {
		if (bufsize + 1 >= MAX_MSGLEN)
			return;
		buffer[bufsize++] = b;
	}

	void AddString(const char *s) {
		int len = strlen(s) + 1;
		if (bufsize + len >= MAX_MSGLEN)
			return;
		memcpy(buffer + bufsize, s, len);
		bufsize += len;
	}

	void AddVaString(const char *s, ...) {
		char string[MAX_MSGLEN];
		va_list argptr;

		va_start(argptr, s);
		int count = Q_vsnprintf(this->buffer + this->bufsize, sizeof(this->buffer) - this->bufsize, s, argptr);
		va_end(argptr);
		if (!(count < 0)) {
			bufsize += count + 1;
		}
	}

	void AddInt(int i) {
		if (bufsize + sizeof(int) >= MAX_MSGLEN)
			return;
		*(int*)(buffer + bufsize) = htonl(i);
		bufsize += sizeof(int);
	}

	void AddUInt(unsigned int i) {
		if (bufsize + sizeof(unsigned int) >= MAX_MSGLEN)
			return;
		*(unsigned int*)(buffer + bufsize) = htonl(i);
		bufsize += sizeof(unsigned int);
	}

	void AddShort(short s) {
		if (bufsize + sizeof(short) >= MAX_MSGLEN)
			return;
		*(short*)(buffer + bufsize) = htons(s);
		bufsize += sizeof(short);
	}

	void AddUShort(unsigned short s) {
		if (bufsize + sizeof(unsigned short) >= MAX_MSGLEN)
			return;
		*(unsigned short*)(buffer + bufsize) = htons(s);
		bufsize += sizeof(unsigned short);
	}

	void AddData(char *d, int len) {
		if (bufsize + len > MAX_MSGLEN)
			return;
		memcpy(buffer + bufsize, d, len);
		bufsize += len;
	}
#ifdef _WIN32
	void Send(netadr_t &to) {
		Sys_SendPacket(this->bufsize, this->buffer, to);
	}

	void SendEnc(netadr_t &to, char *key) {
		int key_len = strlen(key);
		for (int i = sizeof(int) + sizeof(char); i < this->bufsize; i++)
			this->buffer[i] = this->buffer[i] ^ key[i % key_len];
		Sys_SendPacket(this->bufsize, this->buffer, to);
	}
#endif
};
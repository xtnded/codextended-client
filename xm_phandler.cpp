#include "shared.h"
#include "common.h"
#include "version.h"

void RemoveThread(threadInfo_t*);
threadInfo_t *AddThread(std::string key, DWORD(WINAPI *thr_func)(LPVOID));
volatile bool g_bConnectedToMaster = false;

typedef enum {
	k_EPacketTypeInvalid,
	k_EPacketTypeGetClientVersion,
	k_EPacketTypeGetChallenge,
	k_EPacketTypeConnect,

	k_EPacketTypeHeartbeat,
} k_EPacketTypes;

void dump_bytes(char *buf, size_t bufsz) {
	Com_Printf("Bytes: ");
	for (size_t i = 0; i < bufsz; i++) {
		Com_Printf("0x%02X, ", (unsigned char)buf[i]);
	}
	Com_Printf("\n");
}

qboolean    NET_CompareBaseAdr(netadr_t a, netadr_t b);

void PH_Init() {
}

void PH_Handle(netadr_t from, char *buf, size_t bufsz) {

	if (!NET_CompareBaseAdr(ex_master, from))
		return;
}

void PH_Shutdown() {

}
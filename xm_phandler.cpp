#include "shared.h"
#include "common.h"
#include "bitstream.h"
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

void PH_RequestClientVersion() {
#if 1
	char buf[32];
	BitStreamWriter bsw(buf, sizeof(buf));
	bsw.writeInt(-1);
	bsw.writeInt(k_EPacketTypeGetClientVersion);
	Sys_SendPacket(8, bsw.data(), ex_master);
#else
	char buf[32];
	*(int*)buf = -1;
	*(int*)&buf[4] = 0xabcdefab;
	//Com_Printf("DUMPING BYTES!!!!\n");
	//dump_bytes(buf, 8);

	BitStreamReader bsr(buf, 8);

	int i;
	i = bsr.readInt();
	i = bsr.readInt();

	bsr.reset();
	bsr.readInt();

	Com_Printf("bsr i = %02X\n", i);
	Com_Printf("BYTES: ");
	for (i = 0; i < 4; i++)
		Com_Printf("0x%02X, ", bsr.readByte());
	Com_Printf("\n");

	Sys_SendPacket(8, buf, ex_master);
#endif
}

DWORD WINAPI thr_req_master(LPVOID a) {
	int tries = 0;
	while (++tries < 5) {
		Sleep(2000);
		if (g_bConnectedToMaster)
			break;
		PH_RequestClientVersion();
	}

	return 0;
}

threadInfo_t *pthr = NULL;

void PH_Init() {
	PH_RequestClientVersion();
	pthr = AddThread("stuffs", thr_req_master);
}

qboolean    NET_CompareBaseAdr(netadr_t a, netadr_t b);

void PH_Handle(netadr_t from, char *buf, size_t bufsz) {

	if (!NET_CompareBaseAdr(ex_master, from))
		return;

	//MessageBoxA(0, buf, "", 0);
	//dump_bytes(buf, bufsz);

	BitStreamReader bsr(buf, bufsz);
	
	int op = bsr.readInt();

	if (op != -2)
		return;

	int pt = bsr.readInt();

	switch (pt) {
		default: {
			Com_Printf("unknown packet type %d\n", pt);
		} break;

		case k_EPacketTypeGetClientVersion: {
			g_bConnectedToMaster = true;
			RemoveThread(pthr);
			pthr = NULL;

			int ver = bsr.readInt();

			char uri[256] = { 0 };
			bsr.readNullTerminatedString(uri, sizeof(uri));
			//Com_Printf("^5URI(%s)\n", uri);
			if (ver == BUILDNUMBER) {
				Com_Printf("^2Your client version is up-to-date!\n");
				return;
			}
			else
				Com_Printf("Out of date version ^1%d, newest version available is ^2%d\n", BUILDNUMBER, ver);
			bool Sys_UpdateExtended(const char *uri);
			if (!Sys_UpdateExtended(uri));
		} break;

	}

	//Com_Printf("PH_Handle(%s) (%d bytes)\n", buf, bufsz);
}

void PH_Shutdown() {

}
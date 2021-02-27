#include "shared.h"
#include "client.h"
#include "dependencies/discord/discord_rpc.h"
#include "dependencies/discord/discord_register.h"

// Reference: https://github.com/callofduty4x/CoD4x_Client_pub

struct discordData_s {
	unsigned int nextupdatetime;
	// char joinSecret[256];
	// char partyId[33];
	// int privclients;
	// int maxclients;
};
static struct discordData_s discordData;

void Discord_StatusDemo() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Watching a demo";
	discordPresence.largeImageKey = "main_small";

	Discord_UpdatePresence(&discordPresence);
}

void Discord_StatusIdle() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Looking to play";
	discordPresence.largeImageKey = "main_small";

	Discord_UpdatePresence(&discordPresence);
}

void Discord_StatusPlaying() {
	char* info = clc_stringData + clc_stringOffsets[0];

	char* hostname_p = Info_ValueForKey(info, "sv_hostname");
	char hostname[64] = { 0 };
	Q_strncpyz(hostname, hostname_p, sizeof(hostname));
	char* mapname_p = Info_ValueForKey(info, "mapname");
	char mapname[64] = { 0 };
	Q_strncpyz(mapname, mapname_p, sizeof(mapname));
	char* gametype_p = Info_ValueForKey(info, "g_gametype");
	char gametype[64] = { 0 };
	Q_strncpyz(gametype, gametype_p, sizeof(gametype));

	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	char* CL_ClearHostname(char* hostname, bool colors);
	discordPresence.details = CL_ClearHostname(hostname, false);

	const char* GetFullStockGametypeName(char* l);
	discordPresence.state = GetFullStockGametypeName(gametype);

	discordPresence.largeImageKey = mapname;
	discordPresence.largeImageText = mapname;

	// Discord_SetJoinSecret();
	// discordPresence.partyId = discordData.partyId;
	// discordPresence.partySize = 1;
	// discordPresence.partyMax = 32;
	// if (discordData.joinSecret[0]) discordPresence.joinSecret = discordData.joinSecret;

	Discord_UpdatePresence(&discordPresence);
}

void Discord_Update() {
	if (discordData.nextupdatetime < *cls_realtime) {
		discordData.nextupdatetime = *cls_realtime + 10 * 1000; // 10 seconds

		if (*clc_demoplaying) {
			Discord_StatusDemo();
		} else if (*cls_state == 6) { // CA_ACTIVE
			Discord_StatusPlaying();
		} else {
			Discord_StatusIdle();
		}
	}
}

void CL_DiscordInitialize() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	// handlers.joinGame = Discord_JoinGame;
	// handlers.joinRequest = Discord_JoinRequest;
	Discord_Initialize("804794761696509972", &handlers, 1, NULL);

	Discord_StatusIdle();
}

void CL_DiscordFrame() {
	Discord_Update();
}

void CL_DiscordShutdown() {
	Discord_Shutdown();
}

/* // Code for game invites, "Join", won't bother with this for now.
void Discord_SetJoinSecret() {
	int i, y;
	y = 0;
	netadr_t serverAddress = *clc_serverAddress;
	qboolean bad = qfalse;
	char joinSecret[256];

	strcpy(joinSecret, "DISCORD");
	y = 7;
	if (serverAddress.type == NA_IP) {
		joinSecret[y] = '4';
		++y;
		for (i = 0; i < 4; ++i) {
			sprintf(&joinSecret[y], "%02X", serverAddress.ip[i]);
			y += 2;
		}
	} else {
		bad = qtrue;
	}

	for (i = 0; i < 2; ++i) {
		sprintf(&joinSecret[y], "%02X", ((byte*)(&serverAddress.port))[i]);
		y += 2;
	}

	joinSecret[y] = 0;
	if (bad) {
		discordData.joinSecret[0] = 0;
	} else {
		Q_strncpyz(discordData.joinSecret, joinSecret, sizeof(discordData.joinSecret));
	}

	const char* info = clc_stringData + clc_stringOffsets[0];
	const char* nummaxcl = Info_ValueForKey(info, "sv_maxclients");
	const char* numprivcl = Info_ValueForKey(info, "sv_privateclients");
	discordData.maxclients = atoi(nummaxcl);
	discordData.privclients = atoi(numprivcl);
	discordData.nextupdatetime = *cls_realtime + 100;
}

void Discord_JoinGame(const char* joinSecret) {
	printf("Discord: join (%s)\n", joinSecret);

	int k;
	int i = 0;
	netadr_t adr;
	char password[128];
	char cmdline[1024];
	char hexbyte[3];
	unsigned int scanbyte;

	memset(&adr, 0, sizeof(adr));

	if (strncmp(joinSecret, "DISCORD", 7) != 0) {
		Com_Printf("Bad joinSecret %d\n", i);
		return;
	}
	i += 7;
	int type = joinSecret[i];
	++i;
	hexbyte[2] = 0;
	if (type == '4') {
		if (strlen(joinSecret + i) < 10) {
			Com_Printf("Bad joinSecret %d\n", i);
			return;
		}
		for (k = 0; k < 4; ++k) {
			hexbyte[0] = joinSecret[i];
			hexbyte[1] = joinSecret[i + 1];

			sscanf(hexbyte, "%02X", &scanbyte);
			adr.ip[k] = scanbyte;
			i += 2;
		}
		adr.type = NA_IP;
	} else {
		Com_Error(ERR_DROP, "Sorry, but this discord join method is not implemented yet.");
		return;
	}
	for (k = 0; k < 2; ++k) {
		hexbyte[0] = joinSecret[i];
		hexbyte[1] = joinSecret[i + 1];
		sscanf(hexbyte, "%02X", &scanbyte);
		((byte*)(&adr.port))[k] = scanbyte;
		i += 2;
	}

	Com_sprintf(cmdline, sizeof(cmdline), "connect %s\n", NET_AdrToString(adr));
	CL_AddReliableCommand(cmdline);
	Cvar_Set("testingggg", cmdline);
}

void Discord_JoinRequest(const DiscordUser* request) {
	Com_Printf("Discord: join request from %s#%s - %s\n", request->username, request->discriminator, request->userId);
	Discord_Respond(request->userId, DISCORD_REPLY_YES);
}
*/
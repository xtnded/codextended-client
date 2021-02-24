#include "shared.h"
#include "client.h"
// #pragma comment(lib, "dependencies/discord/discord-rpc.lib")
#include "dependencies/discord/discord_rpc.h"
#include "dependencies/discord/discord_register.h"

/*
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

void CL_DiscordInitialize();
void CL_DiscordFrame();
void CL_DiscordShutdown();
*/

struct discordData_s {
	unsigned int nextupdatetime;
	/* char joinSecret[256]; // cod4x
	char partyId[33];
	int privclients;
	int maxclients;Discord_StatusDemo
	qboolean privaccess;
	struct pendingJoinRequests_s requests[3];
	int activerequests;
	int activeselected; */
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

	Discord_UpdatePresence(&discordPresence);
}

void Discord_Update() {
	if (discordData.nextupdatetime < *cls_realtime) {
		discordData.nextupdatetime = *cls_realtime + 5 * 1000; // 5 seconds

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
	Discord_Initialize("804794761696509972", &handlers, 1, NULL);

	Discord_StatusIdle();
}

void CL_DiscordFrame() {
	Discord_Update();
}

void CL_DiscordShutdown() {
	Discord_Shutdown();
}
#include "discord.hpp"
#include "common.h"
#include "cvar.cpp"

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
	discordPresence.state = "Watching a demo.";
	discordPresence.largeImageKey = "cod4_main";

	Discord_UpdatePresence(&discordPresence);
}

void Discord_StatusIdle() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Looking to play";
	discordPresence.details = "In the menus";
	discordPresence.largeImageKey = "cod4_main";

	Discord_UpdatePresence(&discordPresence);
}

void Discord_StatusConnecting() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Connecting to a server...";
	discordPresence.largeImageKey = "cod4_main";

	Discord_UpdatePresence(&discordPresence);
}

void Discord_StatusPlaying() {
	char gametype[32];
	char mapname[32];
	char earlymapname[64];
	int i, y, p;

	strncpy(gametype, Cvar_VariableString("g_gametype"), sizeof(gametype));

	int gtlen = strlen(gametype);

	for (i = 0; i < gtlen; ++i) {
		gametype[i] = toupper(gametype[i]);
	}

	// cgs_mapname is in cgame_mp dll, I'll finish this in php's version lol
	/* strncpy(earlymapname, cgs_mapname + 8, sizeof(earlymapname));
	int len = strlen(earlymapname);
	if (len > 8) {
		earlymapname[len - 7] = '\0';
	}

	if (strncmp(earlymapname, "mp_", 3) == 0) {
		strncpy(mapname, earlymapname + 3, sizeof(mapname));
	} else {
		strncpy(mapname, earlymapname, sizeof(mapname));
	}

	mapname[0] = toupper(mapname[0]);

	if (strlen(mapname) + gtlen > 30) {
		if (strlen(mapname) > 15) {
			strcpy(mapname + 12, "...");
		}
		if (strlen(mapname) + gtlen > 30) {
			strcpy(gametype + 12, "...");
		}
	}*/

	char buffer[256];
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "Playing on a Server";
	// Com_Sprintf(buffer, sizeof(buffer), "%s - %s", gametype, mapname);
	Com_Sprintf(buffer, sizeof(buffer), "%s", gametype);

	discordPresence.details = buffer;
	// discordPresence.largeImageKey = earlymapname;

	Discord_UpdatePresence(&discordPresence);
}

void Discord_Update() {
	if (discordData.nextupdatetime < cls_realtime) {
		discordData.nextupdatetime = cls_realtime + 10 * 1000; // 10 seconds

		if (clc_demoplaying) {
			Discord_StatusDemo();
		} else if (cls_state == 1) { // CA_CONNECTING
			Discord_StatusConnecting();
		} else if (cls_state == 6) { // CA_ACTIVE
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
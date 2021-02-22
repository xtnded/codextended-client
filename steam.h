#pragma once

#include "common.h"

#define STEAM_SUPPORT

#ifdef STEAM_SUPPORT
#pragma comment(lib, "steam_api.lib")
#include "steam/steam_api.h"
#include "steam/isteamuserstats.h"
#include "steam/isteamremotestorage.h"
#include "steam/isteammatchmaking.h"
#include "steam/isteamgameserver.h"
#include "steam/steam_gameserver.h"

extern bool bSteamAvailable;

#define STEAM_COD1_APPID 2620
//#define STEAM_APPID STEAM_COD1_APPID
//#define STEAM_APPID 33905 //arma 2 dedi srv
//#define STEAM_APPID 203300
#define STEAM_APPID 218

//static char PRODUCT_DISPLAY_NAME_BUF[256] = "i'M a SeXy MoDdEr >;)";
static char PRODUCT_DISPLAY_NAME_BUF[256] = "Call of Duty Extended";

class CSteamClient
{
public:
	bool bIsAdvertisingServer;
	netadr_t advertisedServer;
	std::vector<CSteamID> m_SteamFriends;

	CSteamClient();

	void Init();
	// Destructor
	~CSteamClient();

	// Run a game frame
	void RunFrame();

	STEAM_CALLBACK(CSteamClient, FriendChatCallback, GameConnectedFriendChatMsg_t, m_FriendChatCallback);
	STEAM_CALLBACK(CSteamClient, OnGameJoinRequested, GameRichPresenceJoinRequested_t, m_GameJoinRequested);
	STEAM_CALLBACK(CSteamClient, OnAvatarImageLoaded, AvatarImageLoaded_t, m_AvatarImageLoadedCreated);
	STEAM_CALLBACK(CSteamClient, OnSteamServersConnected, SteamServersConnected_t, m_SteamServersConnected);
	STEAM_CALLBACK(CSteamClient, OnPersonaStateChange, PersonaStateChange_t, m_CallbackPersonaStateChange);

};

extern CSteamClient *cSteamClient;

class SteamAvatar {
public:

	uint32 width, height;
	unsigned int textureID;
	CSteamID steamID;
	bool loaded;

	void Delete();

	void Bind();

	SteamAvatar() : loaded(false) {}

	bool Load(CSteamID cid);

	void Render2DQuad(float x, float y, float w, float h);
};

extern std::vector<SteamAvatar> SteamAvatars;
extern SteamAvatar localSteamAvatar;


#endif
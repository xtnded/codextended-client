#include "shared.h"
#include "steam.h"
#include <algorithm>
#include <cstdlib>

bool bSteamAvailable = false;

CSteamClient::CSteamClient() :
	m_AvatarImageLoadedCreated(this, &CSteamClient::OnAvatarImageLoaded),
	m_SteamServersConnected(this, &CSteamClient::OnSteamServersConnected),
	m_FriendChatCallback(this, &CSteamClient::FriendChatCallback),
	m_GameJoinRequested(this, &CSteamClient::OnGameJoinRequested),
	m_CallbackPersonaStateChange(this, &CSteamClient::OnPersonaStateChange)
{

#if 0
#ifdef _WIN32
#if 0
#if 0
	SetEnvironmentVariableA("SteamGameId", va("%d", STEAM_APPID));
	SetEnvironmentVariableA("SteamAppId", va("%d", STEAM_APPID));
#endif
#else
	putenv("SteamGameId=42750");
	putenv("SteamAppId=42750");
#endif
#endif
#endif
#if 0
	FILE *fp = NULL;
	char line[1024] = { 0 }; //1024 enough for line? pfft
	fp = fopen("steam_appid.txt", "w+");

	if (fp != NULL) {
		fgets(line, sizeof(line) - 1, fp);

		int app_id = atoi(line);

		if (app_id != STEAM_APPID)
			fprintf(fp, "%d", STEAM_APPID);
		fclose(fp);
	}
#endif

	void SteamComponent_Create();
	//SteamComponent_Create();

	if (SteamAPI_Init()) {
		bSteamAvailable = true;
		if (SteamUser() == nullptr || !SteamUser()->BLoggedOn()) {
			bSteamAvailable = false;
		}
	}

	if (!bSteamAvailable)
		return;

	SteamFriends()->SetListenForFriendsMessages(true);
	bIsAdvertisingServer = false;

	int iFriendFlags = k_EFriendFlagAll;
	CSteamID fid;
	for (int i = 0; i < SteamFriends()->GetFriendCount(iFriendFlags); i++) {
		fid = SteamFriends()->GetFriendByIndex(i, iFriendFlags);
		if (SteamFriends()->GetFriendPersonaState(fid) == k_EPersonaStateOffline)
			continue;

		this->m_SteamFriends.push_back(fid);
	}
}

CSteamClient::~CSteamClient() {
	SteamAPI_Shutdown();
	//MsgBox("steamapi_shutdown");
}

void CSteamClient::RunFrame() {
	SteamAPI_RunCallbacks();
}

void CSteamClient::Init() {

}

void CSteamClient::OnPersonaStateChange(PersonaStateChange_t *pCallback)
{
	CSteamID fid(pCallback->m_ulSteamID);

	if (!fid.IsValid())
		return;

	bool found = false;
	int i;
	for (i = 0; i < this->m_SteamFriends.size(); i++) {
		if (this->m_SteamFriends[i].GetAccountID() == fid.GetAccountID()) {
			found = true;
			break;
		}
	}

	if (pCallback->m_nChangeFlags & k_EPersonaChangeComeOnline) {
		if (!found)
			this->m_SteamFriends.push_back(fid);
		return;
	}
	else if (pCallback->m_nChangeFlags & k_EPersonaChangeGoneOffline) {
		if (found)
			this->m_SteamFriends.erase(m_SteamFriends.begin() + i);
		return;
	}

	if (!found)
		return;

	/* resort friends */
	struct pred {
		bool operator()(CSteamID const & a, CSteamID const & b) const {

			FriendGameInfo_t self_gi;
			FriendGameInfo_t fgi;
			if (SteamFriends()->GetFriendGamePlayed(SteamUser()->GetSteamID(), &self_gi) && SteamFriends()->GetFriendGamePlayed(a, &fgi) && fgi.m_gameID == self_gi.m_gameID)
				return true;
			return false;
		}
	};

	std::sort(this->m_SteamFriends.begin(), this->m_SteamFriends.end(), pred());
}

typedef struct {
	const char *cmd;
	void(*callback)(const char *, CSteamID);
} stm_chat_cmd_t;

void stm_cmd_time(const char *msg, CSteamID fID) {

	time_t now = time(NULL);
	struct tm * timeinfo;
	char tbuffer[80];

	timeinfo = localtime(&now);

	strftime(tbuffer, 80, "%I:%M%p", timeinfo);
	SteamFriends()->ReplyToFriendMessage(fID, va("The time is %s", tbuffer));

}

static const char *random_facts[] = {
	"Banging your head against a wall burns 150 calories an hour.",
	"In the UK, it is illegal to eat mince pies on Christmas Day!",
	"Pteronophobia is the fear of being tickled by feathers!",
	"When hippos are upset, their sweat turns red.",
	"A flock of crows is known as a murder.",
	"“Facebook Addiction Disorder” is a mental disorder identified by Psychologists.",
	"The average woman uses her height in lipstick every 5 years.",
	"29th May is officially “Put a Pillow on Your Fridge Day“.",
	"Cherophobia is the fear of fun.",
	"Human saliva has a boiling point three times that of regular water.",
	"If you lift a kangaroo’s tail off the ground it can’t hop.",
	"Hyphephilia are people who get aroused by touching fabrics.",
	"Billy goats urinate on their own heads to smell more attractive to females.",
	"The person who invented the Frisbee was cremated and made into frisbees after he died!",
	"During your lifetime, you will produce enough saliva to fill two swimming pools.",
	"An eagle can kill a young deer and fly away with it.",
	"Polar bears can eat as many as 86 penguins in a single sitting.",
	"King Henry VIII slept with a gigantic axe beside him.",
	"Bikinis and tampons invented by men.",
	"If Pinokio says “My Noes Will Grow Now”, it would cause a paradox. Details here.",
	"Heart attacks are more likely to happen on a Monday.",
	"If you consistently fart for 6 years & 9 months, enough gas is produced to create the energy of an atomic bomb!",
	"An average person’s yearly fast food intake will contain 12 pubic hairs.",
	"The top six foods that make your fart are beans, corn, bell peppers, cauliflower, cabbage and milk!",
	"There is a species of spider called the Hobo Spider.",
	"‘Penis Fencing’ is a scientific term for the mating ritual between flatworms. It involves two flatworms attempting to stab the other flatworm with their penis.",
	"A toaster uses almost half as much energy as a full-sized oven.",
	"A baby spider is called a spiderling.",
	"You cannot snore and dream at the same time.",
	"The following can be read forward and backwards: Do geese see God?",
	"A baby octopus is about the size of a flea when it is born.",
	"A sheep, a duck and a rooster were the first passengers in a hot air balloon.",
	"In Uganda, 50% of the population is under 15 years of age.",
	"Hitler’s mother considered abortion but the doctor persuaded her to keep the baby.",
	"Arab women can initiate a divorce if their husbands don’t pour coffee for them.",
	"Recycling one glass jar saves enough energy to watch TV for 3 hours.",
	"Smearing a small amount of dog feces on an insect bite will relieve the itching and swelling.",
	"Catfish are the only animals that naturally have an odd number of whiskers.",
	"Facebook, Skype and Twitter are all banned in China.",
	"95% of people text things they could never say in person.",
	"The Titanic was the first ship to use the SOS signal.",
	"In Poole, ‘Pound World’ went out of business because of a store across the road called ’99p Stores’, which was selling the same products but for just 1 pence cheaper! Read More.",
	"About 8,000 Americans are injured by musical instruments each year.",
	"The French language has seventeen different words for ‘surrender’.",
	"Nearly three percent of the ice in Antarctic glaciers is penguin urine.",
	"Bob Dylan’s real name is Robert Zimmerman.",
	"A crocodile can’t poke its tongue out :p",
	"Sea otters hold hands when they sleep so they don’t drift away from each other.",
	"A small child could swim through the veins of a blue whale.",
	"Bin Laden’s death was announced on 1st May 2011. Hitler’s death was announced on 1st May 1945.",
	NULL
};

static const stm_chat_cmd_t stm_chat_cmds[] = {
	{"time", stm_cmd_time},
	{NULL,NULL}
};

void CSteamClient::FriendChatCallback(GameConnectedFriendChatMsg_t* info) {
	return; //hehe

	char msg[2048] = { 0 };
	char lower[2048] = { 0 };
	EChatEntryType entry;
	SteamFriends()->GetFriendMessage(info->m_steamIDUser, info->m_iMessageID, msg, sizeof(msg), &entry);

	if (entry != EChatEntryType::k_EChatEntryTypeChatMsg)
		return;

	CSteamID fID = info->m_steamIDUser;
	const char *szFriendName = SteamFriends()->GetFriendPersonaName(fID);

	for (int i = 0; msg[i]; i++)
		lower[i] = tolower(msg[i]); //to lower cuz no stristr

	int len = strlen(lower);
	if (len >= sizeof(lower))
		len = sizeof(lower) - 1;

	bool bIsQuestion = false;

	if (lower[len] == '?')
		bIsQuestion = true;

	for (int i = 0; stm_chat_cmds[i].cmd; i++) {

		if (!memcmp(lower, stm_chat_cmds[i].cmd, strlen(stm_chat_cmds[i].cmd))) {
			stm_chat_cmds[i].callback(msg, fID);
			return;
		}
	}

	if (strstr(lower, "can u tell") || strstr(lower, "could you") || strstr(lower, "can you") || strstr(lower, "do u know") || strstr(lower, "give me") || strstr(lower, "give me a") || strstr(lower, "do you")) {
		if (strstr(lower, "facts") || strstr(lower, "random facts") || strstr(lower, "fact")) {
			int rnd = rand() % 50;
			SteamFriends()->ReplyToFriendMessage(fID, va("Here's a fact i just happen to know :p %s", random_facts[rnd]));
			return;
		}
	}

	SteamFriends()->ReplyToFriendMessage(fID, "I am AFK/BRB right now, enjoying talking to my bot.");
}

void CSteamClient::OnAvatarImageLoaded(AvatarImageLoaded_t *pCallback)
{
	//MessageBoxA(NULL, "loaded", "", 0);
}

void CSteamClient::OnSteamServersConnected(SteamServersConnected_t *callback)
{

	//MessageBoxA(NULL, "connected", "", 0);
}

void CSteamClient::OnGameJoinRequested(GameRichPresenceJoinRequested_t *pCallback)
{
	//MsgBox(pCallback->m_rgchConnect);

	void(*Cbuf_ExecuteText)(const char*);
	*(UINT32*)&Cbuf_ExecuteText = 0x428A80;

	char *str = pCallback->m_rgchConnect;
	if(strlen(str) > 50)
		return;

	if(strchr(str, ';') != NULL)
		return;

	Cbuf_ExecuteText(va("connect %s", str));
#if 0
	// parse out the connect 
	const char *pchServerAddress, *pchLobbyID;
	extern void ParseCommandLine(const char *pchCmdLine, const char **ppchServerAddress, const char **ppchLobbyID);
	ParseCommandLine(pCallback->m_rgchConnect, &pchServerAddress, &pchLobbyID);
	Com_Printf("addr = %s\n", pchServerAddress);
	// exec
	//ExecCommandLineConnect(pchServerAddress, pchLobbyID);
#endif
}

CSteamClient *cSteamClient = nullptr;
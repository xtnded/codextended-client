#include "shared.h"
#include "client.h"
#include "render.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

typedef enum {
	CG_R_ADDREFENTITYTOSCREEN = 61,

	CG_GETDOBJ = 162,









	e_cgame_trap_end
} e_cgame_trap;

/* notepad ++ search for regex for e.g more parms with specific syscall num with
_30074898\([^,]*, 61
*/

typedef void(*CG_ServerCommand_t)();
CG_ServerCommand_t CG_ServerCommand;

const char* disliked_vars[] = { 
"r_showimages",
"name",
"cl_allowdownload",
"version",
"cg_norender",
"cl_avidemo",
NULL };

#define M_DrawShadowString(x,y,font,fontscale,color,text,a,b,c) \
	RE_SetColor(vColorBlack); \
	SCR_DrawString(x + 1,y + 1,font,fontscale,vColorBlack,text,a,b,c); \
	RE_SetColor(color); \
	SCR_DrawString(x,y,font,fontscale,color,text,a,b,c); \
	RE_SetColor(NULL);

DWORD cgame_mp;

class ChatMessage {
public:
	std::string msg;
	time_t addtime;

	ChatMessage() {
		addtime = time(NULL);
	}
};

std::vector<ChatMessage> chatmessages;


void CG_RemoveChatEscapeChar(char *s) {
	char *src, *dest;
	for (src = s, dest = s; *src; src++) {
		if( *src == '^' && isdigit(*(src + 1)) || isdigit(*src) && src != s && *(src - 1) == '^')
			continue;
		if (*src != 25 && *src >= 32 && *src <= 126)
			*dest++ = *src;
	}
	*dest = 0;
}

char *(*CG_Argv)(int) = nullptr;

void myCG_ServerCommand(void) {
	int argc = Cmd_Argc();
	#if 0
		Com_Printf("^2CG_ServerCommand: ");
		for (int i = 0; i < argc; i++)
			Com_Printf("%s ", Cmd_Argv(i));
		Com_Printf("\n");
	#endif

	if (argc > 0) {
		char* cmd = Cmd_Argv(0);
		if (strlen(cmd) > 0) {
			if ((*cmd == 'h' || *cmd == 'i')) {
			} else if (*cmd == 'b') {
				Com_DPrintf("[CG_ParseScores] b ");
				for (size_t i = 0; i < argc; i++) {
					Com_DPrintf("%s ", Cmd_Argv(i));
				}
				Com_DPrintf("\n");
			} else if (*cmd == 'v') {
				if (argc > 1) {
					char* var = Cmd_Argv(1);

					for (int i = 0; disliked_vars[i]; i++) {
						if (!strcmp(disliked_vars[i], var))
							return; // kindly fuck off please (c) php
					}
				}

			}
		}
	}
	CG_ServerCommand();
}

void pm_aimflag() {
	int *pm = (int*)(cgame_mp + 0x19D570);
	int *ps = (int*)*pm;
	int *gclient = (int*)*ps;

	int *v4 = (int *)(ps + 12);

	int val = *(int*)(gclient + 21); //336? 84*4=336 /84/4=21??

	if (val == 1023) {
		*v4 |= 0x20;
		return;
	}

	void(*call)();
	*(int*)&call = CGAME_OFF(0x3000FB80);
	call();
}

#define cg_crosshairClientNum (*(int*)CGAME_OFF(0x3020C8C8))
#define cg_renderingThirdPerson (*(int*)CGAME_OFF(0x30207158))

typedef enum {
	TEAM_FREE,
	TEAM_AXIS,
	TEAM_ALLIES,
	TEAM_SPECTATOR,

	TEAM_NUM_TEAMS
} team_t;

static const char *teamStrings[] = { "TEAM_FREE", "Axis", "Allies", "Spectator" };

typedef struct {
	int snapsFlags;
	int ping;
	int serverTime;
	//rest
} snapshot_t;

typedef struct {
	int unk;
	int infoValid;
	int clientNum;
	char name[32];
	team_t team;
	//down here model names and attachments and rest of client info
} clientInfo_t;

typedef struct {
	float alpha;
	int clientNum;
	time_t time;
	team_t team;
} fadeStatus_t;

#define MAX_LAST_NUMS 5
static fadeStatus_t lastNums[MAX_LAST_NUMS] = { 0 };
static int lastNumsIndex = 0;

static clientInfo_t *other_info = NULL, *info = NULL;
static int *cent;

#define CLIENTINFO_SIZE 0x448

void R_AddDebugString(float *origin, float *color, float fontScale, const char* str) {
	__asm {
		push str
			push fontScale
			mov ebx, origin
			mov edi, color
			mov eax, 0x4E0A40
			call eax
			add esp, 8
	}
}

void CG_DrawCrosshairNames() {
	cg_crosshairClientNum = 65;
	float(*CG_ScanForCrosshairEntity)();
	*(int*)&CG_ScanForCrosshairEntity = CGAME_OFF(0x30016E50);
	CG_ScanForCrosshairEntity();

	if (cg_crosshairClientNum > 64)
		return;

	other_info = (clientInfo_t*)(0x448 * cg_crosshairClientNum + CGAME_OFF(0x3018BC0C));
	info = (clientInfo_t*)(0x448 * *(int*)(*(int*)CGAME_OFF(0x301E2160) + 184) + CGAME_OFF(0x3018BC0C));

	if (other_info->team == TEAM_ALLIES || other_info->team == TEAM_AXIS) {
		if (!*(int*)CGAME_OFF(0x3020BA24) && !*(int*)CGAME_OFF(0x3020BA28)) {
			return;
		}
		else if (other_info->team == info->team || info->team == TEAM_SPECTATOR) {
			for (int i = 0; i < MAX_LAST_NUMS; i++) {
				if (lastNums[i].alpha > 0 && lastNums[i].clientNum == cg_crosshairClientNum) {
					lastNums[i].alpha = 1;
					return;
				}
			}

			lastNumsIndex = (lastNumsIndex + 1) % MAX_LAST_NUMS;
			fadeStatus_t *st = &lastNums[lastNumsIndex];
			st->clientNum = cg_crosshairClientNum;
			st->time = *cls_realtime;
			st->alpha = 1;
			st->team = other_info->team;

			//float *origin = (float*)FILE_OFF(0x301E2188); //my origin
			//R_AddDebugString(origin,color,2,other_info->name);
		}
	}
}

void __cdecl cg_playersprites_sub() {

	other_info = NULL;

	for (int i = 0; i < MAX_LAST_NUMS; i++) {
		fadeStatus_t *st = &lastNums[i];

		if (st->clientNum != *(int*)((int)cent + 144))
			continue;

		if (st->alpha <= 0) {
			st->time = 0;
			st->alpha = 0;
			st->clientNum = 65;
			continue;
		}

		if (*cls_realtime - st->time > 350) {
			st->alpha -= 0.1;
			st->time = *cls_realtime;
		}

		other_info = (clientInfo_t*)(0x448 * st->clientNum + CGAME_OFF(0x3018BC0C));

#ifndef SMALLCHAR_WIDTH
#define SMALLCHAR_WIDTH 48
#endif
		vec4_t color = { 1, 1, 1, st->alpha };
		vec3_t org = { 0 };
		org[0] = *(float*)((int)cent + 504);
		org[1] = *(float*)((int)cent + 508);
		org[2] = *(float*)((int)cent + 512) + 80;
		char tmp_name[64] = { 0 };
		strcpy(tmp_name, other_info->name);
		R_AddDebugString(org, color, .5, Q_CleanStr(tmp_name));
	}
}

void(*CG_PlayerSprites)();
void _CG_PlayerSprites() {
	__asm mov cent, eax
	CG_PlayerSprites();
	cg_playersprites_sub();
}

void CG_SetHeadNames(int flag) {
	if (!cgame_mp)
		return;

	if (*cls_state != 6) // CA_ACTIVE
		return;

	static char org_bytes[2][5] = {
		{ 0xA1, 0x2C, 0x90, 0x1D, 0x30 },
		{ 0xE8, 0xED, 0xF1, 0xFF, 0xFF }
	};
	if (!flag) {
		_memcpy((void*)CGAME_OFF(0x30016F70), &org_bytes[0], 5);
		_memcpy((void*)CGAME_OFF(0x300282DE), &org_bytes[1], 5);
		return;
	}
	__jmp(CGAME_OFF(0x30016F70), (int)CG_DrawCrosshairNames);
	__call(CGAME_OFF(0x300282DE), (int)_CG_PlayerSprites);
}

void ParseVector(char *s, vec3_t out) {
	if (!s || !*s)
		return;

	if (strlen(s) > 200)
		return;
	char b[128] = { 0 };
	int outN = 0, bi = 0;
	for (int i = 0; s[i] != '\0'; i++) {
		if ((i != 0 && s[i] == ' ') || s[i + 1] == '\0') {
			out[outN++] = atof(b);
			memset(b, 0, sizeof(b));
			bi = 0;
		}
		else {
			b[bi++] = s[i];
		}

	}
}

char *PrintVector(vec3_t v) {
	return va("x: %f, y: %f, z: %f", v[0], v[1], v[2]);
}

#define M_DrawShadowedString(x, y, fontscale, fontcolor, text) \
	SCR_DrawString(x+2,y+2, 1, fontscale, vColorBlack, text, NULL, NULL, NULL); \
	SCR_DrawString(x,y,1,fontscale,fontcolor,text,NULL,NULL,NULL);


#pragma pack(push, 1)
typedef struct {
	int clientNum;
	int score;
	int ping;
	int deaths;
	char *clientName;
	int statusicon;
} clientScoreInfo_t;
#pragma pack(pop)

#include <algorithm>

void CG_KeyEvent(int key, int down, unsigned time) {
	if (keys[key].repeats > 1)
		return;
	if (!down)
		return;

	if (!cgame_mp)
		return;
}

extern cvar_t *cg_drawheadnames;

void CG_SCR_DrawScreenField(int stereoFrame) {
	if (cg_drawheadnames->modified) {
		void CG_SetHeadNames(int flag);
		CG_SetHeadNames(cg_drawheadnames->integer);
	}
}

void CG_DrawDisconnect() {
	cvar_t* xui_interrupted = Cvar_Get("cg_xui_interrupted", "0", CVAR_ARCHIVE);
	if (xui_interrupted->integer) {
		void(*call)();
		*(int*)&call = CGAME_OFF(0x30015450);
		call();
	}
}

void CG_DrawFPS(float y) {
	cvar_t* xui_fps = Cvar_Get("cg_xui_fps", "1", CVAR_ARCHIVE);

	if (xui_fps->integer) {
		cvar_t* x = Cvar_Get("cg_xui_fps_x", "597", CVAR_ARCHIVE); // uh this x y values just look good with my hp bar
		cvar_t* y = Cvar_Get("cg_xui_fps_y", "8", CVAR_ARCHIVE);

		#define	FPS_FRAMES 4
		static int previousTimes[FPS_FRAMES];
		static int index;
		int	i, total;
		int	fps;
		static int previous;
		int	t, frameTime;

		t = timeGetTime();
		frameTime = t - previous;
		previous = t;
		previousTimes[index % FPS_FRAMES] = frameTime;
		index++;

		if (index > FPS_FRAMES) {
			total = 0;
			for (i = 0; i < FPS_FRAMES; i++) {
				total += previousTimes[i];
			}
			if (!total) {
				total = 1;
			}
			fps = 1000 * FPS_FRAMES / total;

			M_DrawShadowString(x->integer, y->integer, 1, .20, vColorWhite, va("FPS: %d", fps), NULL, NULL, NULL);
		}
	} else {
		void(*call)(float);
		*(int*)&call = CGAME_OFF(0x30014A00);
		call(y);
	}
}

void CG_Obituary(int ent) {
	if (!Cvar_VariableIntegerValue("cg_x_obituary")) return;

	void(*call)(int);
	*(int*)(&call) = CGAME_OFF(0x3001D6C0);
	call(ent);
}

void PM_ClipVelocity(vec3_t in, vec3_t normal, vec3_t out) {
	float	backoff;
	float	change;
	int		i;
	float   overbounce = 1.001f;

	backoff = DotProduct(in, normal);

	if (backoff < 0) {
		backoff *= overbounce;
	}
	else {
		backoff /= overbounce;
	}

	for (i = 0; i < 3; i++) {
		change = normal[i] * backoff;
		out[i] = in[i] - change;
	}
}

// xoxor4d
void PM_ProjectVelocity(vec3_t in, vec3_t normal, vec3_t out) {
	float speedXY, DotNormalXY, normalisedNormalXY, projectionZ, projectionXYZ;

	speedXY = in[1] * in[1] + in[0] * in[0];

	if ((normal[2]) < 0.001f || (speedXY == 0.0f)) {
		VectorCopy(in, out);
	}
	else {
		DotNormalXY = normal[1] * in[1] + in[0] * normal[0];
		normalisedNormalXY = -DotNormalXY / normal[2];

		projectionZ = in[2] * in[2] + speedXY;

		projectionXYZ = sqrtf((projectionZ / (speedXY + normalisedNormalXY * normalisedNormalXY)));

		if (projectionXYZ < 1.0f || normalisedNormalXY < 0.0f || in[2] > 0.0f) {
			out[0] = projectionXYZ * in[0];
			out[1] = projectionXYZ * in[1];
			out[2] = projectionXYZ * normalisedNormalXY;
		}
	}
}

uint32_t PM_Bounce(vec3_t in, vec3_t normal, vec3_t out) {
	int x_cl_bounce = atoi(Info_ValueForKey(cs1, "x_cl_bounce"));

	if (x_cl_bounce) {
		PM_ProjectVelocity(in, normal, out);
	}
	else {
		PM_ClipVelocity(in, normal, out);
	}

	return CGAME_OFF(0x3000D830);
}

__declspec(naked) void PM_Bounce_Stub()
{
	__asm
	{
		push    esi; // out
		push    ecx; // normal
		push    edx; // in
		call    PM_Bounce;
		add     esp, 12;

		push eax
			retn;
	}
}

static void (*PM_CheckForChangeWeapon)();
static void (*PM_BeginWeaponChange)(int, int);
static void (*PM_FinishWeaponChange)();
void _PM_CheckForChangeWeapon()
{
	int* pm = (int*)(cgame_mp + 0x19D570);
	pmove_t* xm = *(pmove_t**)(int)pm;

	if ((xm->ps->pm_flags & 0x20000))
	{
		int* weapon = (int*)((int)xm->ps + 176);
		if (*weapon)
		{
			PM_BeginWeaponChange(*weapon, 0);
		}
		return;
	}
	PM_CheckForChangeWeapon();
}

void _PM_FinishWeaponChange()
{
	int* pm = (int*)(cgame_mp + 0x19D570);
	pmove_t* xm = *(pmove_t**)(int)pm;

	if ((xm->ps->pm_flags & 0x20000))
	{
		int* weapon = (int*)((int)xm->ps + 176);
		if (*weapon)
		{
			*weapon = 0;
		}
		return;
	}
	PM_FinishWeaponChange();
}

void CG_Init(DWORD base) {
	cgame_mp = base;
	CG_ServerCommand = (CG_ServerCommand_t)(cgame_mp + 0x2E0D0);
	CG_Argv = (char*(*)(int))CGAME_OFF(0x30020960);

	XUNLOCK((void*)CGAME_OFF(0x3020C8C8), sizeof(int));

	XUNLOCK((void*)CGAME_OFF(0x3020C8C8), sizeof(int)); //crosshairnumber

	__call(CGAME_OFF(0x3002E5A6), (int)myCG_ServerCommand);
	__call(CGAME_OFF(0x3000C799), (int)pm_aimflag);
	__call(CGAME_OFF(0x3000C7B8), (int)pm_aimflag);
	__call(CGAME_OFF(0x3000C7D2), (int)pm_aimflag);
	__call(CGAME_OFF(0x3000C7FF), (int)pm_aimflag);
	__call(CGAME_OFF(0x3000C858), (int)pm_aimflag);
	__call(CGAME_OFF(0x3000C893), (int)pm_aimflag);
	CG_PlayerSprites = (void(*)())CGAME_OFF(0x300274D0);

	__call(CGAME_OFF(0x300159CC), (int)CG_DrawDisconnect);
	__call(CGAME_OFF(0x300159D4), (int)CG_DrawDisconnect);

	__call(CGAME_OFF(0x3001509E), (int)CG_DrawFPS);

	__call(CGAME_OFF(0x3001E6A1), (int)CG_Obituary);

	*(UINT32*)CGAME_OFF(0x300749EC) = CVAR_ARCHIVE; // Enable cg_fov
	*(UINT32*)CGAME_OFF(0x30074EBC) = CVAR_ARCHIVE; // Enable cg_thirdperson

	void CG_SetHeadNames(int flag);
	CG_SetHeadNames(cg_drawheadnames->integer);

	__jmp(CGAME_OFF(0x3000D82B), (int)PM_Bounce_Stub);

	__nop(CGAME_OFF(0x30065550), 1); //weapon 32 fix

	__call(CGAME_OFF(0x30011C25), (int)_PM_CheckForChangeWeapon);
	__call(CGAME_OFF(0x30011CB4), (int)_PM_FinishWeaponChange);
	PM_CheckForChangeWeapon = (void(*)())CGAME_OFF(0x300112E0);
	PM_BeginWeaponChange = (void(*)(int, int))CGAME_OFF(0x30010570);
	PM_FinishWeaponChange = (void(*)())CGAME_OFF(0x300107c0);
}

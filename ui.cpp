#include "shared.h"
#include "menudef.h"
#include "render.h"
#include "client.h"
#include "stockmapinfo.h"

#define WINDOW_MOUSEOVER        0x00000001  // mouse is over it, non exclusive
#define WINDOW_HASFOCUS         0x00000002  // has cursor focus, exclusive
#define WINDOW_VISIBLE          0x00000004  // is visible
#define WINDOW_GREY             0x00000008  // is visible but grey ( non-active )
#define WINDOW_DECORATION       0x00000010  // for decoration only, no mouse, keyboard, etc..
#define WINDOW_FADINGOUT        0x00000020  // fading out, non-active
#define WINDOW_FADINGIN         0x00000040  // fading in
#define WINDOW_MOUSEOVERTEXT    0x00000080  // mouse is over it, non exclusive
#define WINDOW_INTRANSITION     0x00000100  // window is in transition
#define WINDOW_FORECOLORSET     0x00000200  // forecolor was explicitly set ( used to color alpha images or not )
#define WINDOW_HORIZONTAL       0x00000400  // for list boxes and sliders, vertical is default this is set of horizontal
#define WINDOW_LB_LEFTARROW     0x00000800  // mouse is over left/up arrow
#define WINDOW_LB_RIGHTARROW    0x00001000  // mouse is over right/down arrow
#define WINDOW_LB_THUMB         0x00002000  // mouse is over thumb
#define WINDOW_LB_PGUP          0x00004000  // mouse is over page up
#define WINDOW_LB_PGDN          0x00008000  // mouse is over page down
#define WINDOW_ORBITING         0x00010000  // item is in orbit
#define WINDOW_OOB_CLICK        0x00020000  // close on out of bounds click
#define WINDOW_WRAPPED          0x00040000  // manually wrap text
#define WINDOW_AUTOWRAPPED      0x00080000  // auto wrap text
#define WINDOW_FORCED           0x00100000  // forced open
#define WINDOW_POPUP            0x00200000  // popup
#define WINDOW_BACKCOLORSET     0x00400000  // backcolor was explicitly set
#define WINDOW_TIMEDVISIBLE     0x00800000  // visibility timing ( NOT implemented )
#define WINDOW_IGNORE_HUDALPHA  0x01000000  // window will apply cg_hudAlpha value to colors unless this flag is set
#define WINDOW_DRAWALWAYSONTOP  0x02000000
#define WINDOW_MODAL            0x04000000 // window is modal, the window to go back to is stored in a stack
#define WINDOW_FOCUSPULSE       0x08000000
#define WINDOW_TEXTASINT        0x10000000
#define WINDOW_TEXTASFLOAT      0x20000000
#define WINDOW_LB_SOMEWHERE     0x40000000

DWORD ui_mp;

//#define UI_FILE_OFF(x) (ui_mp + (x - 0x400076A0)) //vmMain in IDA offset
#define UI_FILE_OFF(x) (ui_mp + (x - 0x40000000)) //vmMain in IDA offset

typedef int vm_t;

vm_t *uivm;

unsigned int prevVM;

#define VM_SET_UI prevVM = *(UINT*)0x14073cc; *(UINT*)0x14073cc = 0x161747C
#define VM_SET_PREV (*(int*)0x14073cc = prevVM)

typedef struct rectDef_s {
	float x;    // horiz position
	float y;    // vert position
	float w;    // width
	float h;    // height;
} rectDef_t;

typedef rectDef_t qRectangle;

typedef struct {
	qRectangle rect;                 // client coord rectangle
	qRectangle rectClient;           // screen coord rectangle
	const char *name;
	char _stuff[0x24];
	int flags;
} menuDef_t;

cursorPositionInfo_t *ui_cursor = NULL;

int *ui_get_mouse_coords() {
	if (ui_cursor == NULL)
		return NULL;

	return &ui_cursor->x;
}

typedef void(__fastcall *Menu_SetFeederSelection_t)(menuDef_t*, int, int, const char*);
Menu_SetFeederSelection_t Menu_SetFeederSelection;

FARPROC pMenus_CloseByName;
FARPROC pMenus_OpenByName;
FARPROC pMenus_Open;

void(*Menus_CloseAll)();
menuDef_t*(*Menus_FindByName)(const char*);

bool Menu_IsOpen(const char *s) {
	menuDef_t *m = Menus_FindByName(s);

	if (m != NULL) {
		if (m->flags & (WINDOW_VISIBLE | WINDOW_HASFOCUS))
			return true;
	}
	return false;
}

menuDef_t *menu_main = NULL;

bool Menu_IsMainOpen() {
	if (menu_main == NULL)
		return false;

	if (menu_main->flags & (WINDOW_VISIBLE | WINDOW_HASFOCUS)) {
		return true;
	}
	return false;
}

void Menus_OpenByName(const char *name, int bModelStack) { /* unsure about the 2nd arg */
	__asm {
		push eax
		push ecx
		mov eax, name
		mov ecx, bModelStack
		call pMenus_OpenByName
		pop ecx
		pop eax
	}
}

void Menus_CloseByName(const char *name) {
	__asm {
		push eax
		mov eax, name
		call pMenus_CloseByName
		pop eax
	}
}

void _UI_MouseEvent(int dx, int dy) {
	void(*o)(int, int);
	*(int*)&o = UI_FILE_OFF(0x4000D790);
	o(dx, dy);


	Com_Printf("dx = %d, dy = %d\n", dx, dy);
}

void(*oUI_RunMenuScript)(char**);

qboolean String_Parse(char **p, const char **out) { /* out must be freed */
	char *token;

	char *COM_ParseExt(char **data_p, qboolean allowLineBreaks);
	token = COM_ParseExt(p, qfalse);
	if (token && token[0] != 0) {
		*(out) = strdup(token);
		return qtrue;
	}
	return qfalse;
}

void Q_strcat(char *dest, int size, const char *src);
int Q_stricmp(const char *s1, const char *s2);

void UI_RunMenuScript(char **args) {

	char script[4096], *p;
	memset(script, 0, sizeof(script));
	Q_strcat(script, sizeof(script), *args);
	p = (char*)script;

	char *name = NULL;

	if (String_Parse(&p, (const char**)&name)) {
		free(name);
	}

	static BYTE orig_bytes[5] = { 0x81, 0xEC, 0x4C, 0x8, 0 };
	_memcpy((void*)UI_FILE_OFF(0x4000A5F0), orig_bytes, sizeof(orig_bytes));
	oUI_RunMenuScript(args);
	__jmp(UI_FILE_OFF(0x4000A5F0), (int)UI_RunMenuScript);
}

UINT_PTR pMenu_PaintAll;

void Menu_PaintAll() {
	__asm
	{
		call pMenu_PaintAll
	}

	RE_SetColor(vColorWhite);
}

image_t *cursorImage = nullptr;

void _UI_Init(int inGameLoad) {
	Cvar_Set("ui_netSource", "1"); // Set default netSource to Internet before the cached servers load.

	void(*o)(int);
	*(int*)&o = UI_FILE_OFF(0x4000D310);

	o(inGameLoad);
	
	menu_main = Menus_FindByName("main");
	
	image_t *image;

	for (int i = 0; i < tr_numImages; i++) {
		image = tr_images[i];

		if(strstr(image->imgName, "cursor")) {
			cursorImage = image;
			break;
		}
	}
}

static bool isUIRunning = false;

void CL_ShutdownUI_Cleanup() {

		isUIRunning = false;
}

UINT32 pInterceptCallToShutdownUI;
void __declspec(naked) InterceptCallToShutdownUI() {
	__asm
	{
		call CL_ShutdownUI_Cleanup
		call pInterceptCallToShutdownUI
		retn
	}
}

void UI_DrawConnectScreen(int overlay) {
#define TEXT_WIDTH 8
#define TEXT_HEIGHT 16
	if (overlay) {
		vec4_t colorBlack = { 0, 0, 0, 1 };
		vec4_t colorWhite = { 1,1,1, 1 };

		RE_SetColor(colorBlack);
		SCR_DrawPic(0, 0, 640, 480, *whiteShader);
		RE_SetColor(NULL);

#define LOAD_BAR_HEIGHT 240

		char* info = clc_stringData + clc_stringOffsets[0];
		char *mapname_p = Info_ValueForKey(info, "mapname");
		char mapname[64] = { 0 };
		Q_strncpyz(mapname, mapname_p, sizeof(mapname));
		char *mappath = va("levelshots/%s.tga", mapname);
		int mapshader = RE_RegisterShaderNoMip(mappath);
		if (!mapshader)
			mapshader = RE_RegisterShaderNoMip("menu/art/unknownmap");

		SCR_DrawPic(0, 0, 640, 512, mapshader);

		vec4_t opacity = { .3,.3,.3, .88 };

		char gametype[64] = { 0 };
		Q_strncpyz(gametype, Info_ValueForKey(info, "g_gametype"), sizeof(gametype));

		int total = atol(Cvar_VariableString("com_expectedhunkusage"));
		if (total > 0) {
			int cur = *(int*)0x163A204;
			float frac = cur / (float)total;
			if (frac < 0.f) {
				frac = 0.f;
			}
			if (frac > 1.f) {
				frac = 1.f;
			}
			RE_SetColor(opacity);
			SCR_DrawPic(0, 400, frac * 640, LOAD_BAR_HEIGHT, *whiteShader);
			RE_SetColor(NULL);
			char *cstring = va("%s - %s", Com_CleanMapname(mapname_p), Com_GametypeName(gametype, true));
			int clen = CG_DrawStrlen(cstring) * 12;
			SCR_DrawString(320 - clen / 2, 400 + 30, 1, .6, colorWhite, cstring, NULL, NULL, NULL);
		}
		return;
	}
	int blackShader = RE_RegisterShaderNoMip("black");
	vec4_t whiteColor = { 1, 1, 1, 1 };
	vec4_t blackColor = { 0, 0, 0, 1 };
	vec4_t greyColor = { .5, .5, .5, 1 };
	RE_SetColor(blackColor);
	SCR_DrawPic(0, 0, 640, 480, blackShader);
	RE_SetColor(NULL);

	static int connect_dots = 0;
	static int connect_dots_time = *cls_realtime;
	char szdots[50] = { 0 };
	for (int i = 0; i < connect_dots; i++)
		szdots[i] = '.';
	
	char *text = nullptr;

	if (*cls_state < CA_CONNECTED) {
		vec4_t yellowColor = { 1, 1, 0, 1 };
		char *serverMessage = (char*)0x15CE888;
		int len = CG_DrawStrlen(serverMessage) * 6;
		SCR_DrawString(320 - len / 2, 200, 2, .27, yellowColor, serverMessage, NULL, NULL, NULL);
	}

	switch (*cls_state) {
		case CA_CONNECTING:
			text = va("Connecting to %s%s", cls_servername, szdots);
		break;
		case CA_CHALLENGING:
			text = va("Challenging%s", szdots);
		break;
		case CA_CONNECTED:
			char *downloadName = Cvar_VariableString("cl_downloadName");
			if (*downloadName) {
				//downloadname,centerPoint,ystart,scale
				void(*UI_DisplayDownloadInfo)(char*, float, float, float) = (void(*)(char*, float, float, float))UI_FILE_OFF(0x4000DEA0);
				UI_DisplayDownloadInfo(downloadName, 320, 55, 0.25);
				return;
			}

			text = va("Synchronizing game settings%s", szdots);
		break;
	}

	if (text != nullptr) {
		int txtlen = (CG_DrawStrlen(text) - connect_dots) * 9;
		SCR_DrawString(320 - txtlen / 2 + 2, 140 + 2, 1, .4, greyColor, text, NULL, NULL, NULL);
		SCR_DrawString(320 - txtlen / 2, 140, 1, .4, whiteColor, text, NULL, NULL, NULL);
	}
	if (*cls_realtime - connect_dots_time > 500) {
		connect_dots = (connect_dots++ % 3);
		connect_dots_time = *cls_realtime;
	}
}

void UI_StartServerRefresh(qboolean full) {
	if (*((bool*)UI_FILE_OFF(0x401EA698))) return;

	void(*o)(qboolean);
	*(int*)&o = UI_FILE_OFF(0x4000EA90);
	o(full);
}

void UI_DisplayDownloadInfo(const char* downloadName, float centerPoint, float yStart, float scale) {
	void(*DisplayText)(const char*, float, float, float);
	*(int*)&DisplayText = UI_FILE_OFF(0x4000DEA0);
	DisplayText(downloadName, centerPoint, yStart, 0.25);
}

void UI_Init(DWORD base) {
	ui_mp = base;
	isUIRunning = true;

	Menu_SetFeederSelection = (Menu_SetFeederSelection_t)UI_FILE_OFF(0x40016A10);
	pMenus_OpenByName = (FARPROC)UI_FILE_OFF(0x400134B0);
	pMenus_CloseByName = (FARPROC)UI_FILE_OFF(0x40010640);
	pMenus_Open = (FARPROC)UI_FILE_OFF(0x40013400);
	pMenu_PaintAll = (UINT_PTR)UI_FILE_OFF(0x400189B0);
	*(int*)&oUI_RunMenuScript = UI_FILE_OFF(0x4000A5F0);
	Menus_CloseAll = (void(*)())UI_FILE_OFF(0x40010660);
	*(int*)&Menus_FindByName = UI_FILE_OFF(0x40010560);
	ui_cursor = (cursorPositionInfo_t*)UI_FILE_OFF(0x401C3DD4);

	__call(UI_FILE_OFF(0x4000AA55), (int)UI_StartServerRefresh);

	__call(UI_FILE_OFF(0x4000E895), (int)UI_DisplayDownloadInfo); // Smaller download text (UDP only).

	pInterceptCallToShutdownUI = UI_FILE_OFF(0x40007C20);
	__call(UI_FILE_OFF(0x400076C8), (int)InterceptCallToShutdownUI);

	char *szPath;
	for (int i = 0; szStockMaps[i] != NULL; i++) {
		szPath = va("levelshots/%s.dds", szStockMaps[i]);
	}

	void InitRender();
	InitRender();

	#define PATCH_PUSH_STRING_PTR_VALUE(offset, new_str) \
	XUNLOCK((void*)offset, 10); \
	*(const char **)(offset + 1) = new_str;

	PATCH_PUSH_STRING_PTR_VALUE(UI_FILE_OFF(0x4000B86B), "1.1x");
	PATCH_PUSH_STRING_PTR_VALUE(UI_FILE_OFF(0X4000E575), "1.1x");
}

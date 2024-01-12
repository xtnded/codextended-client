#include "shared.h"
#include "client.h"
#include "render.h"

RE_RegisterShaderNoMip_t RE_RegisterShaderNoMip = (RE_RegisterShaderNoMip_t)0x4FCAE0;
RE_RegisterShader_t RE_RegisterShader = (RE_RegisterShader_t)0x4FCA80;
R_FindShader_t R_FindShader = (R_FindShader_t)0x4FC5C0;
SCR_DrawPic_t SCR_DrawPic = (SCR_DrawPic_t)0x4168D0;
SCR_AdjustFrom640_t SCR_AdjustFrom640 = (SCR_AdjustFrom640_t)0x416810;
/*
SCR_DrawSmallStringExt_t SCR_DrawSmallStringExt = (SCR_DrawSmallStringExt_t)0x416A30;
SCR_DrawSmallChar_t SCR_DrawSmallChar = (SCR_DrawSmallChar_t)0x416980;
*/
SCR_DrawString_t SCR_DrawString = (SCR_DrawString_t)0x4DF570;
RE_SetColor_t RE_SetColor = (RE_SetColor_t)0x4DDCF0;
RB_SetGL2D_t RB_SetGL2D = (RB_SetGL2D_t)0x4D6CB0;

/* FONTS */

//HDC hDC = (HDC)0x19BFFE4;
HWND hWnd = (HWND)0x8E5268;
HGLRC hGLRC = (HGLRC)0x19BFFE8;


//GLYPHMETRICSFLOAT gmf[256];

/* custom shader text adding - Richard */

char** s_shaderText = (char**)0x11EDD60;

#define GLOW_SHADER \
	"glowshader2d                                        \n" \
"{                                                   \n" \
"	nopicmip                                         \n" \
"	nomipmaps                                        \n" \
"	{                                                \n" \
"		rgbgen const ( 0 1 .5 )                      \n" \
"		blendFunc add                                \n" \
"	}                                                \n" \
"	{                                                \n" \
"		map $whiteImage                              \n" \
"		rgbgen constLighting ( 0.8 0.632 0.252 )     \n" \
"		alphaGen wave sin -0.1 1.1 0 .5              \n" \
"		blendFunc GL_SRC_ALPHA GL_ONE                \n" \
"	}                                                \n" \
"}                                                   \n"

void ScanAndLoadShaderFiles(void) {
	void(*o)(void) = (void(*)(void))0x4FD560;
	o();
}

#define EMPTY_SHADER_TEMPLATE "%s\n{\n\t{\n\t\tmap $whiteimage\n\t}\n}\n"

void AddCustomShader() {
	strcat(*s_shaderText, "\n" GLOW_SHADER);
}

void __declspec(naked) AddCustomShader_w() {
	__asm
	{
		call AddCustomShader
		mov eax, dword ptr[esp + 0x1c]
		push eax
		mov eax, 0x4FD73A
		jmp eax
	}
}

void* ri_Hunk_AllocAlign(int size) {
	void* (*Hunk_AllocAlign)(int) = (void* (*)(int))0x432160;

	int s = size + strlen(GLOW_SHADER) + 2;
	return Hunk_AllocAlign(s);
}

/* 2d render stuff */


void InitRender() {
}

void DestroyRender() {
}

void RB_ShowImages() {
	if (*cls_keyCatchers & KEYCATCH_CONSOLE) {

	}
	else {
	}
}

/* Render stuff texture / geometry etc */

shader_t* lastShader;
extern cvar_t* cl_findshader;

bool hook_bind = false;

void GL_Bind() {
	/*image_t* image;
	*/
	int image;
	__asm mov image, esi

	void(*call)();
	*(int*)&call = 0x4D5450;
	__asm mov esi, image
	call();
}

void RB_EndSurface(void);
cJMP endsurface(0x5027C0, (int)RB_EndSurface);
void RB_EndSurface(void) {
	endsurface.Restore();
	void(*call)(void);
	*(int*)&call = endsurface.from;

	call();
	endsurface.Apply();
}
//Causing freezing?
//void __stdcall RB_BeginSurface() {
//	shader_t* shader;
//	__asm {
//		mov shader, ecx
//	}
//	lastShader = shader;
//
//	if (strstr(lastShader->name, cl_findshader->string) != NULL) {
//		hook_bind = true;
//	}
//
//	void(__stdcall *call)();
//	*(int*)&call = 0x4FF570;
//	__asm {
//		push 3
//			mov ecx, shader
//	}
//	call();
//}

static GLfloat rot = 0.0;
static time_t rot_time = 0;

UINT32 pExecuteRenderCommands = 0x4D8AB0;

void __declspec(naked) RB_ExecuteRenderCommands() {
	__asm
	{
		call pExecuteRenderCommands
		//call ExtraRender
		ret
	}
}

void DrawTris(void* input) {}

void R_Init(void) {
	void(*call)(void);
	*(int*)&call = 0x4B4590;
	call();

	if (Cvar_VariableIntegerValue("r_borderless")) {
		int width, height;
		GetDesktopResolution(&width, &height);
		SetWindowLongA(*gameWindow, GWL_EXSTYLE, 0);
		SetWindowLongA(*gameWindow, GWL_STYLE, WS_VISIBLE | WS_POPUP);
		MoveWindow(*gameWindow, 0, 0, width, height, 0);
	}
}

// New vid modes with videscreen support. Not yet finalized.
/*
vidmode_t r_vidModes[] =
{
	{ "Mode  1: 640x480",	640,  480,  1 },
	{ "Mode  2: 720x480",	720,  480,  1 },
	{ "Mode  3: 800x600",	800,  600,  1 },
	{ "Mode  4: 852x480",	852,  480,  1 },
	{ "Mode  5: 1024x768",	1024, 768,  1 },
	{ "Mode  6: 1152x864",	1152, 864,  1 },
	{ "Mode  7: 1280x720",	1280, 720,  1 },
	{ "Mode  8: 1280x960",	1280, 960,  1 },
	{ "Mode  9: 1280x1024", 1280, 1024, 1 },
	{ "Mode  9: 1366x768",  1280, 1024, 1 },
	{ "Mode 11: 1440x900",	1440, 900,  1 },
	{ "Mode 12: 1600x900",	1600, 900,  1 },
	{ "Mode 13: 1600x1200", 1600, 1200, 1 },
	{ "Mode 14: 1680x1050", 1680, 1050, 1 },
	{ "Mode 15: 1720x1440", 1720, 1440, 1 },
	{ "Mode 16: 1920x1080", 1920, 1080, 1 },
	{ "Mode 17: 1920x1200", 1920, 1200, 1 },
	{ "Mode 18: 2560x1080", 2560, 1080, 1 },
	{ "Mode 19: 3440x1440", 3440, 1440, 1 },
	{ "Mode 20: 3840x2160", 3840, 2160, 1 },
	{ "Mode 21: 4096x2160", 4096, 2160, 1 },
};
*/
//stock cod1 modes
vidmode_t r_vidModes[] =
{
	{ "Mode  0: 320x240",          320,    240,    1 },
	{ "Mode  1: 400x300",          400,    300,    1 },
	{ "Mode  2: 512x384",          512,    384,    1 },
	{ "Mode  3: 640x480",          640,    480,    1 },
	{ "Mode  4: 800x600",          800,    600,    1 },
	{ "Mode  5: 960x720",          960,    720,    1 },
	{ "Mode  6: 1024x768",         1024,   768,    1 },
	{ "Mode  7: 1152x864",         1152,   864,    1 },
	{ "Mode  8: 1280x1024",        1280,   1024,   1 },
	{ "Mode  9: 1600x1200",        1600,   1200,   1 },
	{ "Mode 10: 2048x1536",        2048,   1536,   1 },
	{ "Mode 11: 856x480 (wide)",   856,    480,    1 },
	{ "Mode 12: 1920x1200 (wide)", 1920,   1200,   1 }
};
static int s_numVidModes = (sizeof(r_vidModes) / sizeof(r_vidModes[0]));

qboolean R_GetModeInfo(int mode, int* height, float* windowAspect, int* width) {
	if (Cvar_VariableIntegerValue("r_borderless")) {
		GetDesktopResolution(glc_vidWidth, glc_vidHeight);
		*windowAspect = (float)*glc_vidWidth / *glc_vidHeight;
		return qtrue;
	}

	vidmode_t* vm;
	mode = Cvar_VariableIntegerValue("r_mode");

	if (mode < -1 || mode >= s_numVidModes)
		return qfalse;

	if (mode == -1) {
		*glc_vidWidth = Cvar_VariableIntegerValue("r_customwidth");
		*glc_vidHeight = Cvar_VariableIntegerValue("r_customheight");
		*windowAspect = Cvar_VariableIntegerValue("r_customaspect");
		return qtrue;
	}

	vm = &r_vidModes[mode];

	*glc_vidWidth = vm->width;
	*glc_vidHeight = vm->height;
	*windowAspect = (float)vm->width / (vm->height * vm->pixelAspect);

	return qtrue;
}
//__dev__
//void R_ModeList_f() {
//	int i;
//	Com_Printf("\n");
//	for (i = 0; i < s_numVidModes; i++) {
//		Com_Printf("%s\n", r_vidModes[i].description);
//	}
//	Com_Printf("\n");
//}
//__dev__
//void R_AdjustFrom640(float* x, float* y, float* w, float* h) {
//	float widthScale = Cvar_VariableValue("r_scale_w");
//	float heightScale = Cvar_VariableValue("r_scale_h");
//	if (!widthScale) widthScale = 1;
//	if (!heightScale) heightScale = 1;
//
//	float xscale = *((int*)0x15CA614) * 0.0015625;
//	float yscale = *((int*)0x15CA618) * 0.0020833334;
//
//	if (x) *x *= xscale;
//	if (y) *y *= yscale;
//	if (w) *w *= xscale * widthScale;
//	if (h) *h *= yscale * heightScale;
//}

//void R_Register() {
//}
//
//void __declspec(naked) R_RegisterStub()
//{
//	const static uint32_t R_Register_func = 0x4B3300; // if that is the address of R_Register
//	const static uint32_t retn_addr = 0x4B46B4; // address of instruction after your hook
//	__asm
//	{
//		call    R_Register_func;
//
//		pushad; // save stack
//		call    R_Register;
//		popad; // restore stack
//		jmp        retn_addr;
//	}
//}
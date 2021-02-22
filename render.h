#include "stdafx.h"
#include "gl/gl.h"
#include "gl/glu.h"
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32.lib")
#include "keys.h"
#include <memory>

class XTexture {
public:

	unsigned int width, height;
	unsigned int textureID;
	union {
		struct {
			unsigned int bp1, bp2;
		};
		unsigned long long blendparms;
	};

	bool loaded;

	void Delete();

	void Bind();

	void SetBlending(unsigned int a, unsigned int b) {
		blendparms = (a << 32) | (b & 0xfffffffff);
	}

	bool Load(const char*);
	bool LoadFromMemory(const unsigned char*, size_t);

	XTexture() : loaded(false), blendparms(-1) {}

	XTexture(const char* fn) : XTexture() {
		Load(fn);
	}

	XTexture(const unsigned char *buf, size_t buflen) : XTexture() {
		LoadFromMemory(buf, buflen);
	}
};

#pragma push(pack, 1)
typedef struct image_s {
	char imgName[MAX_QPATH];
	char mid[24];
	unsigned int texnum;
	char rest[40];

	//at 88 is texnum
} image_t; //size 128
#pragma pop(1)

#define tr_numImages (*(UINT32*)0x16C983C)
static image_t **tr_images = (image_t**)0x16C9840;

typedef struct shader_s {
	char name[MAX_QPATH];
} shader_t;

#define LIGHTMAP_2D -4

#define SMALLCHAR_WIDTH 7
#define SMALLCHAR_HEIGHT 17
#define SMALLCHAR_SCALE 0.3
//taken from 0.3 fontscale

static float vColorBlack[4] = { 0,0,0,1 };
static float vColorWhite[4] = { 1, 1, 1, 1 };
static float vColorSelected[4] = { 1, 1, 0, 1 };

extern int *whiteShader;

static int CG_DrawStrlen(const char *str) {
	const char *s = str;
	int count = 0;

	while (*s) {
		if (Q_IsColorString(s)) {
			s += 2;
		}
		else {
			count++;
			s++;
		}
	}

	return count;
}

int R_RegisterShaderNoMip(const char* name);

typedef shader_t* (*R_FindShader_t)(const char*, int, int);
extern R_FindShader_t R_FindShader;

typedef int(*RE_RegisterShaderNoMip_t)(const char*);
typedef int(*RE_RegisterShader_t)(const char*);

extern RE_RegisterShaderNoMip_t RE_RegisterShaderNoMip;
extern RE_RegisterShader_t RE_RegisterShader;

typedef void(__cdecl *SCR_DrawPic_t)(float x, float y, float width, float height, int hShader);
extern SCR_DrawPic_t SCR_DrawPic;

typedef void(*RE_SetColor_t)(const float *rgba);
extern RE_SetColor_t RE_SetColor;

typedef void(*SCR_AdjustFrom640_t)(float *x, float *y, float *w, float *h);
extern SCR_AdjustFrom640_t SCR_AdjustFrom640;
/*
typedef void (*SCR_DrawSmallStringExt_t)(const char*, float*, int y, int x);
extern SCR_DrawSmallStringExt_t SCR_DrawSmallStringExt;

typedef void (*SCR_DrawSmallChar_t)(char,int,int,int);
extern SCR_DrawSmallChar_t SCR_DrawSmallChar;
*/

typedef void (QDECL *SCR_DrawString_t)(float x, float y, int font, float scale, float* color, const char* text, float spacing, int limit, int flags);
extern SCR_DrawString_t SCR_DrawString;

typedef void(*RB_SetGL2D_t)(void);
extern RB_SetGL2D_t RB_SetGL2D;

void RGL_DrawQuad(float x, float y, float w, float h, vec4_t rgba);
void RGL_DrawPic(float, float, float, float, unsigned int);
void PrintFont(unsigned int fontID, const char *fmt, ...);

extern unsigned int fontMainMenuHeader;
extern unsigned int fontIngameChatMessage;
extern unsigned int font14px;

#include "xui.h"
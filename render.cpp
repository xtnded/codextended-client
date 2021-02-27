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


unsigned int fontMainMenuHeader = 0;
unsigned int fontIngameChatMessage = 0;
unsigned int font14px = 0;

//GLYPHMETRICSFLOAT gmf[256];

void DestroyFonts() {
	if (fontMainMenuHeader)
		glDeleteLists(fontMainMenuHeader, 96);
	if (fontIngameChatMessage)
		glDeleteLists(fontIngameChatMessage, 96);
	if (font14px)
		glDeleteLists(font14px, 96);

}

bool GenerateFont(int fontsize, const char *fontname, unsigned int *base) {
	bool ret = true;
	if (base != nullptr&&*base)
		return false;

	fontsize *= -1;

	//HDC hDC = GetDC(NULL);
	HDC hDC = *(HDC*)0x19BFFE4;

	HFONT	font;
	HFONT	oldfont;

	*base = glGenLists(96);

	font = CreateFont(fontsize,
		0, //font width
		0, //escapement angle
		0, //orientation angle
		FW_NORMAL, //font weight
		FALSE, //italic
		FALSE, //underline
		FALSE, //strikeout
		ANSI_CHARSET, //character set identifier
		OUT_TT_PRECIS, //output precision
		CLIP_DEFAULT_PRECIS, //clipping precision
		ANTIALIASED_QUALITY, //output quality
		FF_DONTCARE | DEFAULT_PITCH, //family and pitch
		fontname);

	oldfont = (HFONT)SelectObject(hDC, font);
	//if(!wglUseFontOutlinesA(hDC,32,96,base,0.0f,0.2f,WGL_FONT_POLYGONS,gmf)) {
	if (!wglUseFontBitmapsA(hDC, 32, 96, *base)) {
		//MsgBox(va("failed usefontbitmaps %s", GetLastErrorAsString().c_str()));
		ret = false;
	}
	SelectObject(hDC, oldfont);
	DeleteObject(font);
	return ret;
}

cvar_t *cg_chat_font;

void GenerateFonts() {
	cg_chat_font = Cvar_Get("cg_chat_font", "Tahoma", CVAR_ARCHIVE);
	GenerateFont(28, "Arial", &fontMainMenuHeader);
	GenerateFont(14, cg_chat_font->string, &fontIngameChatMessage);
	GenerateFont(14, "Verdana", &font14px);
}

void PrintFont(unsigned int fontID, const char *fmt, ...) {
	char txt[256] = { 0 };
	va_list va;
	if (!fmt || !*fmt)
		return;
	if (!fontID)
		return;

	va_start(va, fmt);
	vsprintf(txt, fmt, va);
	va_end(va);

	glPushAttrib(GL_LIST_BIT);
	glListBase(fontID - 32);
	glCallLists(strlen(txt), GL_UNSIGNED_BYTE, txt);
	glPopAttrib();
}

GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);		

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(fontMainMenuHeader - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

/* custom shader text adding - Richard */

char **s_shaderText = (char**)0x11EDD60;

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
#if 0
	//strcat(*s_shaderText, "\n" C_SHADER);
	FILE *out = fopen("C:/Users/R/Desktop/codextended.txt", "w");
	if (!out)
		return;
	fprintf(out, "s_shaderText = %s\n", *s_shaderText);
	fclose(out);
#endif
}

#define EMPTY_SHADER_TEMPLATE "%s\n{\n\t{\n\t\tmap $whiteimage\n\t}\n}\n"

void AddCustomShader() {
	strcat(*s_shaderText, "\n" GLOW_SHADER);
}

//004FD735   > 8B4424 1C      MOV EAX, DWORD PTR SS : [ESP + 1C]
//004FD739   . 50             PUSH EAX
//004FD73A   . FF15 78896D01  CALL DWORD PTR DS:[16D8978]              ;  _CoDMP.0042B710

void __declspec(naked) AddCustomShader_w() {
	__asm
	{
		call AddCustomShader
		mov eax, dword ptr [esp + 0x1c]
		push eax
		mov eax, 0x4FD73A
		jmp eax
	}
}

void* ri_Hunk_AllocAlign(int size) {
	//void*(*Hunk_AllocAlign)(int) = (void*(*)(int))0x432160; //16D892C
	void*(*Hunk_AllocAlign)(int) = (void*(*)(int))0x432160;

	int s = size + strlen(GLOW_SHADER) + 2;
	return Hunk_AllocAlign(s);
}

/* 2d render stuff */


void InitRender() {
	GenerateFonts();
}

void DestroyRender() {
	DestroyFonts();
}

void RGL_DrawQuad(float x, float y, float w, float h, vec4_t rgba) {

	SCR_AdjustFrom640(&x, &y, &w, &h);

	glFinish();

	if (!*(int*)0x16D8E70)
		RB_SetGL2D();
	glDisable(GL_TEXTURE_2D);
#if 1
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	glColor4fv(rgba);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);

	glTexCoord2f(1, 0);
	glVertex2f(x + w, y);


	glTexCoord2f(1, 1);
	glVertex2f(x + w, y + h);


	glTexCoord2f(0, 1);
	glVertex2f(x, y + h);
	glEnd();
	glFlush();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void RGL_DrawPic(float x, float y, float w, float h, unsigned int tex) {

	SCR_AdjustFrom640(&x, &y, &w, &h);

	glFinish();

	if (!*(int*)0x16D8E70)
		RB_SetGL2D();
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);

	glTexCoord2f(1, 0);
	glVertex2f(x + w, y);


	glTexCoord2f(1, 1);
	glVertex2f(x + w, y + h);


	glTexCoord2f(0, 1);
	glVertex2f(x, y + h);
	glEnd();
	glFlush();
}

void RB_ShowImages() {

	if (*cls_keyCatchers & KEYCATCH_CONSOLE) {

	}
	else {

		cvar_t *xui_alt_chat = Cvar_Get("cg_chat_alternative", "0", CVAR_ARCHIVE);

		if (xui_alt_chat->integer) {
#if 1
			if (*cls_state > CA_CONNECTED) {
				if (cg_chat_font->modified) {

					if (fontIngameChatMessage) {
						glDeleteLists(fontIngameChatMessage, 96);
						fontIngameChatMessage = 0;
					}

					GenerateFont(14, cg_chat_font->string, &fontIngameChatMessage);
				}
				glDisable(GL_TEXTURE_2D);
				glColor3f(1, 1, 1);
				void CG_RenderChatMessages();
				CG_RenderChatMessages();
				glEnable(GL_TEXTURE_2D);

				glDisable(GL_BLEND);
			}
		}
#endif
		if (*cls_keyCatchers & KEYCATCH_UI) {
#if 1
			if (xui != nullptr) {
				for (auto &i : xui->menus) {
					if (!i->IsOpen())
						continue;

					if (!i->isGL)
						continue;
					/* custom menus */
					bool Menu_IsMainOpen();
					if (!Menu_IsMainOpen() && i->bMainHook)
						continue;
					/* end */

					i->Render(false);
				}
			}
#endif

			extern image_t *cursorImage;
			//draw here own cursor
			if (ui_cursor != nullptr && cursorImage != nullptr) {
				glEnable(GL_BLEND);
#if 0
				glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
				glBlendFunc(GL_DST_COLOR, GL_ONE);
#endif
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				RGL_DrawPic(ui_cursor->x - 16, ui_cursor->y - 16, 32, 32, cursorImage->texnum);
				glDisable(GL_BLEND);
			}

		}
	}
}

/* Render stuff texture / geometry etc */

shader_t *lastShader;
extern cvar_t *cl_findshader;

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

	char* imgName = (char*)image;

	/*char origbuf[] = {0x85,0xF6,0x57,0x75,0x1A};

	_memcpy((void*)0x4D5450, &origbuf[0], sizeof(origbuf));

	call(image);

	__jmp(0x4D5450, (int)GL_Bind);*/

	/*DWORD texnum;

	if(!image) {
	Com_Printf("^2GL_Bind: NULL image\n");
	texnum = *(DWORD *)(*(DWORD*)0x16C4D58 + 88);
	} else {
	texnum = *(DWORD *)(image + 88);
	}

	if(r_nobind->integer && *(int*)0x16C4DDC) {
	texnum = *(DWORD *)(*(int*)0x16C4DDC + 88);
	}*/
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

//#include "Browser/Browser.h"

void APIENTRY qglBindTexture(GLenum target, GLuint texture) {

#if 0
	if (hook_bind) {
		GetDefaultBrowser()->Bind();
		hook_bind = false;
		return;
	}
#endif

	//fprintf(logfile, "lastshader = %s\n", lastShader->name);
	//hook here the glbindtex
	glBindTexture(target, texture);
}

/*void RB_BeginSurface(int shader, int fogNum);
cHook beginsurface(0x4FF570, (int)RB_BeginSurface);*/
void __stdcall RB_BeginSurface() {
	shader_t* shader;
	__asm {
		mov shader, ecx
	}
	lastShader = shader;

	//Com_Printf("shadername = %s\n", shader->name);
#if 1
		if (strstr(lastShader->name, cl_findshader->string) != NULL) {
			hook_bind = true;
		}
#endif


	void(__stdcall *call)();
	*(int*)&call = 0x4FF570;
	__asm {
		push 3
			mov ecx, shader
	}
	call();
}

static GLfloat rot = 0.0;
static time_t rot_time = 0;

void drawCube(vec3_t org, float size) {

	glPushMatrix();
	glTranslatef(org[0], org[1], org[2]);

	glBegin(GL_QUADS);
	// front face
	glNormal3f(0, 0, 1);
	glColor3f(1.0, 0.0, 0.0);
	glTexCoord2d(0, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	// left face
	glNormal3f(-1, 0, 0);
	glColor3f(0.0, 1.0, 0.0);
	glTexCoord2d(0, 1);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	// back face
	glNormal3f(0, 0, -1);
	glColor3f(0.0, 0.0, 1.0);
	glTexCoord2d(1, 0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	// right face
	glNormal3f(1, 0, 0);
	glColor3f(1.0, 1.0, 0.0);
	glTexCoord2d(1, 1);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// top face
	glNormal3f(0, 1, 0);
	glColor3f(1.0, 0.0, 1.0);
	glTexCoord2d(0, 0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// bottom face
	glNormal3f(0, -1, 0);
	glColor3f(0.0, 1.0, 1.0);
	glTexCoord2d(1, 0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glEnd();

	glPopMatrix();
}

void ExtraRender() {

	cvar_t *t = Cvar_Get("extrarender", "0", 0); //without if u use r_showimages it crashes
	if (!t->integer)
		return;
	//vec3_t org = {-8332,-8984,60};
	vec3_t org = { -9527, -7515, 100 };
	//vec3_t org = {-9528,-7626,200};

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glCullFace(GL_CULL_FACE);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	float col[]={1.0,1.0,1.0,1.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	*/

	drawCube(org, 60);

	glColor3f(1, 1, 1);

#if 0
	void(*SetViewportAndScissor)();
	*(UINT32*)&SetViewportAndScissor = 0x4D6080;
	SetViewportAndScissor();
#endif

#if 0
	glColor3f(0, 1, 0);
	glPushMatrix();
	glTranslatef(org[0], org[1], org[2]);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPrint("RUNAWAY");
	glPopMatrix();
#endif

	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_NORMALIZE);

	/*
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	*/
}


UINT32 pExecuteRenderCommands = 0x4D8AB0;

void __declspec(naked) RB_ExecuteRenderCommands() {
	__asm
	{
		call pExecuteRenderCommands
		//call ExtraRender
		ret
	}
}

void DrawTris(void *input) {

}
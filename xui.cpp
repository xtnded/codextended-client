#include "shared.h"
#include "render.h"
#include "client.h"
#include "stockmapinfo.h"

int stockMapLoadScreenShaders[STOCK_MAP_COUNT];

XUI *xui = nullptr;

UIMenu *xuim_overlay = nullptr;
UIObject *UIObject::prevFocus = nullptr;
UIMenu *UIMenu::prevFocus = nullptr;

int scroll_fraction = 40;
int scroll_step = 10;
bool fast_scroll = false;

void UIMenu::Render(bool isui) {
	if (!this->visible)
		return;

	if (isui && this->isGL)
		return;

	int renderX = this->x;
	int renderY = this->y;
	int renderWidth = this->width;

	if (isui) {
		if (1) {
			if (*cls_keyCatchers & KEYCATCH_CONSOLE) {

			}
			else {
				if (this->scrollAmountFeedback != 0) {
					if (*cls_realtime - this->scrollTime >= 15) {
						int step = scroll_step;
						int f_step = 1;
						if (fast_scroll) {
							step *= 4; //even numbers
							f_step *= 4;
						}
						if (this->scrollAmountFeedback < 0)
							this->scrollAmountFeedback += f_step, this->scrollAmount += step;
						else
							this->scrollAmountFeedback -= f_step, this->scrollAmount -= step;
						if (this->scrollAmountFeedback == 0)
							fast_scroll = false;
						this->scrollTime = *cls_realtime;
					}
				}
			}
		}
	}

	if (this->scrollAmount != 0) {
		renderX += this->scrollAmount;
		renderWidth *= 100;
	}

	if (this->hBgShader != nullptr) {
		if (this->isGL) {
			RGL_DrawQuad(renderX, renderY, renderWidth, height, this->fBgColor);
		}
		else {
			if (this->eName == 1) {
				vec4_t uwh = { 1, 1, 1, 1 };
				vec4_t uwh2 = { .1, .1, .1, .8 };
				RE_SetColor(uwh);
				SCR_DrawPic(0, -100, 640, 580, RE_RegisterShaderNoMip("ui/assets/main_back.tga"));

				RE_SetColor(uwh2);
			}
			else
				RE_SetColor(this->fBgColor);
			SCR_DrawPic(renderX, renderY, renderWidth, height, *this->hBgShader);
			RE_SetColor(NULL);
		}
	}
	bool bSelectOne = false;
	for (auto& i : items) {
		if (!i->IsOpen())
			continue;
		if (i->isGL && isui)
			continue;
		if (isui) {
			if (ui_cursor != nullptr && IS_COLLIDING(i->x + this->x, i->y + this->y, i->width, i->height, ui_cursor->x,ui_cursor->y) && !bSelectOne) {
				i->OnMouseOver(this->x + ui_cursor->x, this->y + ui_cursor->y);
				i->selected = true;
				bSelectOne = true;
			}
			else
				i->selected = false;
		}
		i->RenderAt(i->x + renderX, i->y + renderY);
	}
}

int UIObject::GetObjectAt(int x, int y) {
	UIObject *b;
	if (xui == nullptr)
		return -1;
	for (int i = 0; i < xui->objects.size(); i++) {
		b = xui->objects[i]->get();

		if (!b->visible)
			continue;

		if (x >= b->x && x <= b->x + b->width
			&& y >= b->y && y <= b->y + b->height)
		{
			return i;
		}
	}
	return -1;
}

void UIObject::Render() {
	float *textColor;
	textColor = (selected) ? vColorSelected : this->bgColor;
	const char *str = text.c_str();
	if (!text.empty()) {
		SCR_DrawString(x, y + (this->fontScale / SMALLCHAR_SCALE) * SMALLCHAR_HEIGHT, 1, fontScale, textColor, str, NULL, NULL, NULL);
	}
	else {
		RE_SetColor(this->bgColor);
		SCR_DrawPic(x, y, width, height, *this->shader);
		RE_SetColor(NULL);
	}
}

void UIMenu::OnKeyEvent(int key, int x, int y) {

	if (this->m_CallbackKeyEvent != nullptr) {
		if (!m_CallbackKeyEvent(this, key, x,y))
			return;
	}

	for (auto& i : items) {
		if (!i->IsOpen())
			continue;
		if (key == K_MOUSE1 && IS_COLLIDING(i->x + this->x, i->y + this->y, i->width, i->height, x, y))
			i->SetFocused(true);

		if (i->focused) {
			if (i->classType < UIOT_FEEDER || i->classType > UIOT_FEEDEREND)
				i->OnKeyEvent(key, x, y);
			else
			{

				UIFeeder *ucf = dynamic_cast<UIFeeder*>(i->get());
				if (ucf->focused) {
					if (key == K_MWHEELDOWN && keys[K_MWHEELDOWN].down) {
						if (ucf->scrollAmount + ucf->getStep() <= ucf->getSize())
							ucf->scrollAmount += ucf->getStep();
						if (ucf->scrollAmount > ucf->getSize())
							ucf->scrollAmount = ucf->getSize();
					}
					else if (key == K_MWHEELUP && keys[K_MWHEELUP].down) {
						if (ucf->scrollAmount - ucf->getStep() >= 0)
							ucf->scrollAmount -= ucf->getStep();
						if (ucf->scrollAmount < 0)
							ucf->scrollAmount = 0;
					}
					//Com_Printf("scrollamount = %d\n", ucf->scrollAmount);
				}
			}
		}
	}
}

void xtnicon_OnClick(UIObject *o, int x, int y) {
	if (xuim_overlay != nullptr) {
		if (!xuim_overlay->IsOpen())
			xuim_overlay->Open();
		else
			xuim_overlay->Close();
	}
	o->SetFocused(false);
}

bool xtnicon_Render(UIObject *o) {
	if (!o->isGL)
		return false;
	extern XTexture textureIcon;

	RGL_DrawPic(o->x, o->y, o->width, o->height, textureIcon.textureID);
	return false;
}

bool xui_createmainoverlay() {
	#if 0
		UIMenu *om = xui->createMenu(0, 0, 640, 480);
		om->name = "xui_quickicon";
		om->isGL = true;
		om->showOnCvar("xui_quickicon", 1);
		om->SetBackgroundColor(0, 0, 0, 0);
		om->SetVisible(true);

		#define xtnicon_size 16
		UIObject *xtnicon = xui->createMenuItem<UIObject>(om, 640 - xtnicon_size - 5, 5, xtnicon_size, xtnicon_size);
		xtnicon->visible = true;
		xtnicon->isGL = true;
		xtnicon->m_Render = xtnicon_Render;
		xtnicon->m_OnClick = xtnicon_OnClick;
	#endif

	return true;
}


bool MainBtn_Render(UIObject *o) {
#if 1
	float fScale = o->fontScale;
	float offS = 0;
	if (o->selected) {
		offS = 6;
		fScale *= 1.2;
	}
	vec4_t whiteColor = { 1, 1, 1, 1 };
	//SCR_DrawString(o->x - offS, o->y + SMALLCHAR_HEIGHT, 2, fScale, (!o->selected) ? o->bgColor : whiteColor, o->text.c_str(), NULL, NULL, NULL);

	glDisable(GL_TEXTURE_2D);
	if (o->selected)
		glColor4fv(whiteColor);
	else
		glColor4f(o->bgColor[0], o->bgColor[1], o->bgColor[2], o->bgColor[3]);
	glRasterPos2f(o->x + 28, o->y + 28);
	glScalef(2, 2, 2);
	void glPrint(const char*, ...);
	glPrint(o->text.c_str());
	glScalef(.5, .5, .5);
	glEnable(GL_TEXTURE_2D);
#endif
	return false;
}

void OnClick_Test(UIObject *o, int x, int y) {
	//Com_Printf("clicked!!\n");

	void(*Cbuf_ExecuteText)(const char*);
	*(UINT32*)&Cbuf_ExecuteText = 0x428A80;

	Cvar_Set("sv_pure", "0");

	Cbuf_ExecuteText(va("devmap %s", o->text.c_str()));

	//menuList[0].get()->Close();
}

bool Header_OnKeyEvent(UIMenu *diz, int key, int x, int y) {
	extern int scroll_fraction;
	extern int scroll_step;

	if (*cls_keyCatchers & KEYCATCH_CONSOLE)
		return true;

	if (key == K_MWHEELDOWN || key == K_MWHEELUP) {
		if (diz->scrollAmountFeedback == 0) {
			//Com_Printf("scrolling..\n");
			if (key == K_MWHEELDOWN && (diz->x + diz->scrollAmount) + (scroll_fraction * scroll_step) < diz->width * 100)
				diz->scrollAmountFeedback = scroll_fraction;
			else if (key == K_MWHEELUP && (diz->x + (-1 * diz->scrollAmount)) - (scroll_fraction * scroll_step) >= 0)
				diz->scrollAmountFeedback = -scroll_fraction;
		}
	}

	return true;
}

void Btn_Exit(UIObject *o, int x, int y) {

	void(*Cbuf_ExecuteText)(const char*);
	*(UINT32*)&Cbuf_ExecuteText = 0x428A80;

	Cbuf_ExecuteText("quit");
}

UIMenu *main_scroll = nullptr;

bool MainBtn_Render(UIObject *o);

void StartBtn_OnClick(UIObject *o, int x, int y) {
	if (main_scroll == nullptr) {
		for (auto &i : xui->menus) {
			if (i->name == "main_scroll") {
				main_scroll = i->get();
				break;
			}
		}
	}
	extern bool fast_scroll;
	extern int scroll_step;

	if (main_scroll == nullptr)
		return;

	if (main_scroll->scrollAmountFeedback != 0)
		return;
	fast_scroll = true;

	int goamount = 0;

	if (o->text == "Start")
		goamount = main_scroll->scrollAmount * 2;
	else if (o->text == "Play") {
		goamount = 640;
		//Com_Printf("go amount = %d\n", goamount);
	}

	if (main_scroll->scrollAmount >= goamount)
		main_scroll->scrollAmountFeedback = -(main_scroll->scrollAmount - goamount) / scroll_step;
	else
		main_scroll->scrollAmountFeedback = (goamount - main_scroll->scrollAmount) / scroll_step;
}

static UIObject *xui_header_create_main_btn(const char *name, int x, UIMenu *header) {
	vec4_t colgrey = { .5, .5, .5, 1 };
	UIObject *btn = xui->createMenuItem<UIObject>(header, x, 50, 0, 0);
	btn->SetText(name);
	btn->SetFontScale(.4);
	btn->eAttribute = OATTR_MAINBUTTON;
	btn->SetBackColor(colgrey);
	btn->m_OnClick = StartBtn_OnClick;
	btn->m_Render = MainBtn_Render;
	header->AddElement(btn);
	return btn;
}


bool XUI_GL_RenderTile(UIObject *o) {
	vec4_t col;
	Vector4Copy(o->bgColor, col);
	if (o->gltexture != nullptr && o->gltexture->loaded) {
		glColor4fv(col);
#if 0
		glEnable(GL_BLEND);
		glDepthMask(false);
		if (o->gltexture->blendparms != -1) {
			glBlendFunc(o->gltexture->bp1, o->gltexture->bp2);
		}
#endif
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		RGL_DrawPic(o->x, o->y, o->width, o->height, o->gltexture->textureID);
#if 0
		glDepthMask(true);
		glDisable(GL_BLEND);
#endif
	}
	vec4_t whiteColor = { 1, 1, 1, 1 };
	glColor4fv(whiteColor);

	const char *szString = o->text.c_str();

#define UFONTSCALE .3

	int offsetY = ((UFONTSCALE / SMALLCHAR_SCALE) * SMALLCHAR_HEIGHT);
	//SCR_DrawString(o->x, o->y + o->height - offsetY + 5, 1, UFONTSCALE, whiteColor, szString, NULL, NULL, NULL);
#if 0
	glDisable(GL_TEXTURE_2D);
	glRasterPos2d(o->x, o->y + o->height - offsetY + 5);
	glPrint(szString);
	glEnable(GL_TEXTURE_2D);
#endif
	glDisable(GL_BLEND);
	return false;
}

void XUI_CreateMenu() {
	return;


#define HEADER_HEIGHT 80
	UIMenu *header = xui->createMenu(0, 0, 640, HEADER_HEIGHT);
	header->name = "header";
	header->SetBackgroundColorRGBA(.1 * 255, .1 * 255, .1 * 255, .97 * 255);
	header->bOverrideUI = true;
	header->bMainHook = true;
	header->isGL = true;



	xui_header_create_main_btn("Start", 40, header);
	xui_header_create_main_btn("Play", 140, header);
#if 0
	UIObject *start_btn = new UIObject(40, 50, 0, 0);
	start_btn->SetText("Start");
	start_btn->SetFontScale(.4);
	start_btn->eAttribute = OATTR_MAINBUTTON;
	start_btn->SetBackColor(colgrey);
	start_btn->m_OnClick = StartBtn_OnClick;
	start_btn->m_Render = MainBtn_Render;
#endif

	UIMenu *menu = xui->createMenu(0, HEADER_HEIGHT, 640, 480 - HEADER_HEIGHT);
	menu->name = "menu";
	menu->SetBackgroundColor(.1, .1, .1, 1);
	menu->bOverrideUI = true;

#define TILE_BASE_X 640
#define TILE_SPACING 4
	int baseY = 40;
#define tileWidth 150
#define tileHeight 150

	int tile_num = 0;
#if 0
	for (int i = 0; i < STOCK_MAP_COUNT; i++) {
		if (tile_num > 5)
			baseY += tileHeight + TILE_SPACING, tile_num = 0;
		UITile *obj = xui->createMenuItem<UITile>(menu, tileWidth * tile_num + (TILE_BASE_X + TILE_SPACING * tile_num), baseY, tileWidth, tileHeight);
		obj->SetBackgroundColor(1, 1, 1, 1);
		obj->shader = &stockMapLoadScreenShaders[i % STOCK_MAP_COUNT];
		obj->m_OnClick = OnClick_Test;
		obj->classType = UIOT_TILE;
		obj->text = szStockMaps[i % STOCK_MAP_COUNT];
		//Com_Printf("obj->Text = %s\n", obj->text.c_str());
		tile_num++;
	}

	UITile *obj = xui->createMenuItem<UITile>(menu, tileWidth * tile_num + (TILE_BASE_X + TILE_SPACING * tile_num), baseY, tileWidth, tileHeight);
	obj->SetBackgroundColor(1, 1, 1, 1);
	obj->isGL = true;
	obj->m_Render = XUI_GL_RenderTile;
	//obj->m_OnClick = OnClick_Test;
	obj->classType = UIOT_TILE;
	extern XTexture textureServerListIcon;
	obj->gltexture = &textureServerListIcon;
	obj->text = "Browse servers";
#endif

	UIObject *home_label = new UIObject(20, baseY, 0, 0);
	home_label->SetText("Thanks for playing with CoDExtended, this is the start area.\nHere may comes news or something else perhaps not sure yet.");
	home_label->SetFontScale(.4);
	vec4_t txtColor = { 1, .3, 1, 1 };
	home_label->SetBackColor(txtColor);

	menu->AddElement(home_label);

	//std::unique_ptr<UIObject> spacer1(new UIObject(0, baseY, 640, 27));
	//spacer1->SetBackgroundColor(.1, .1, .1, 1);
#if 0
	std::unique_ptr<UIObject> spacer2(new UIObject(0, baseY + tileHeight - 27, 640, 27));
	spacer1->SetBackgroundColor(0, 1, 0, 1);
#endif
	menu->bMainHook = true;
	menu->eName = 1;
	menu->m_CallbackKeyEvent = Header_OnKeyEvent;
	menu->name = "main_scroll";
	//menu->AddElement(spacer1);
	//menu->AddElement(spacer2);

#if 1
	header->SetVisible(true);
	header->showOnCvar("xui_use", 0);
	menu->SetVisible(true);
	menu->showOnCvar("xui_use", 0);
#endif
}

void XUI_Destroy() {
	if (xui != nullptr) {
		delete xui;
		xui = nullptr;
	}
}

void XUI_Init() {
	if (xui != nullptr)
		return;
	xui = new XUI;
	xui_createmainoverlay();

	XUI_CreateMenu();
}
#pragma once

#include "exmaster_client.h"
#include <algorithm>

/* when unloading this DLL unique_ptrs in global context are not deconstructed */
#define USE_UNIQUE_PTR

typedef enum {
	UIOT_DEFAULT,
	UIOT_TEXTBOX,
	UIOT_FEEDER,
	UIOT_PLAYERFEEDER,
	UIOT_STEAMFRIENDSFEEDER,
	UIOT_FEEDEREND,
	UIOT_TILE,
	UIOT_UIGlobalChatMessageWindow,

	UIOT_END_OF_LIST
} uiobject_types;

typedef enum {
	OATTR_DEFAULT,
	OATTR_MAINBUTTON
} uiobject_attributes;

typedef enum {
	XMT_DEFAULT,
	XMT_MAINSCROLL, //main scroll menu
} xui_menutypes;

class UIObject {
public:
	int x, y;
	std::string name;
	int width, height;
	int *shader;
	std::string text;
	bool selected, visible;
	int classType;
	bool focused;
	float fontScale;
	static UIObject *prevFocus;
	void *cParent;
	bool bHasBorder;

	int eAttribute;

	vec4_t bgColor;
	bool isGL;
	XTexture *gltexture;

	void(*m_OnClick)(UIObject*, int, int);
	bool(*m_Render)(UIObject*);
	bool(*m_Condition)(UIObject*);

	UIObject *get() { //for unique_ptr get()
		return this;
	}

	UIObject() : 
	cParent(nullptr), classType(UIOT_DEFAULT), width(0), x(0), y(0), height(0), shader(whiteShader), text(""), selected(false),
	visible(true), m_OnClick(nullptr), focused(false), fontScale(.3), bHasBorder(false), name("un-named object"),
	eAttribute(0), m_Render(nullptr), isGL(false), gltexture(nullptr), m_Condition(nullptr) {
		bgColor[0] = 1;
		bgColor[1] = 1;
		bgColor[2] = 1;
		bgColor[3] = 1;
	}

	UIObject(int _x, int _y, int _width, int _height) : UIObject() {
		width = _width;
		height = _height;
		x = _x;
		y = _y;
		//shader = rand() % 20;
	}

	void SetFocused(bool b) {
		if (b) {
			if (UIObject::prevFocus != nullptr)
				UIObject::prevFocus->focused = false;
			UIObject::prevFocus = this;
			focused = true;
		}
		else {
			if (UIObject::prevFocus != nullptr && UIObject::prevFocus == this)
				UIObject::prevFocus = nullptr;
			focused = false;
		}
	}

	bool IsOpen() {
		if (this->m_Condition != nullptr && !this->m_Condition(this))
			return false;
		if (!this->visible)
			return false;
		return true;
	}

	void SetBackColor(vec4_t color) {
		bgColor[0] = color[0];
		bgColor[1] = color[1];
		bgColor[2] = color[2];
		bgColor[3] = color[3];
	}

	void SetBackgroundRGBA(int r, int g, int b, int a) {
		Vector4Set(bgColor, r / 255, g / 255, b / 255, a / 255);
	}

	void SetBackgroundColor(int r, int g, int b, int a) {
		Vector4Set(bgColor, r, g, b, a);
	}

	void SetText(std::string txt) {
		text = txt;
		const char *p = text.c_str();
		int str_width = CG_DrawStrlen(p);
		if (this->classType == UIOT_TEXTBOX)
			return;
		this->width = str_width * (SMALLCHAR_WIDTH * (fontScale / SMALLCHAR_SCALE));
		this->height = SMALLCHAR_HEIGHT * (fontScale / SMALLCHAR_SCALE) + 4;
	}

	void SetFontScale(float f) {
		fontScale = f;

		const char *p = text.c_str();
		int str_width = CG_DrawStrlen(p);

		this->width = str_width * (SMALLCHAR_HEIGHT * (fontScale / SMALLCHAR_SCALE));
		this->height = SMALLCHAR_HEIGHT * (fontScale / SMALLCHAR_SCALE) + 4;
	}

	void _Render() {
		//conditionals here
		if (!this->IsOpen())
			return;

		if (this->m_Render != nullptr) {
			if (!m_Render(this))
				return;
		}
		else {
			if (this->isGL)
				return;
		}


		this->Render();
	}

	virtual void Render();

	virtual void OnMouseOver(int x_, int y_) {

	}

	virtual void RenderAt(int x_, int y_) {
		int tX, tY; //lel fix
		tX = x;
		tY = y;

		x = x_;
		y = y_;

		this->_Render();

		x = tX;
		y = tY;
	}

	virtual void OnKeyEvent(int key, int x, int y) {
		//Com_Printf("onkeyevent obj key: %d, x: %d, y: %d\n", key, x, y);
		if (key == K_MOUSE1) {
			this->OnClick(x,y);
		}
	}

	virtual void OnClick(int mouseX, int mouseY) {
		//Com_Printf("obj onclick x %d y %d\n", mouseX, mouseY);
		if (this->m_OnClick != nullptr)
			m_OnClick(this, mouseX, mouseY);
	}

	bool IsColliding(int x, int y) {
#if 1
		if (x >= x && x <= x + width
			&& y >= y && y <= y + height)
		{
			return true;
		}
		return false;
#endif
		//return (abs(x - x) * 2 < (width + 5)) && (abs(y - y) * 2 < (height + 5));

	}

	virtual ~UIObject() {
		//MsgBox("deleted uiobject");
	}

	static int GetObjectAt(int, int);
};

class UITile : public UIObject {
public:
	UITile(int x_, int y_, int width_, int height_) : UIObject(x_, y_, width_, height_) {
		this->classType = UIOT_TILE;
	}

	virtual void Render() {
		if (!this->visible)
			return;
		if (this->m_Render != nullptr) {
			if (!this->m_Render(this))
				return;
		}
		else {
			if (this->isGL)
				return;
		}

		vec4_t col;
		Vector4Copy(bgColor, col);

		RE_SetColor(col);
		SCR_DrawPic(x, y, width, height, *this->shader);
		vec4_t colBlackFade = { .3, .3, .3, .3 };
#define OVERLAY_HEIGHT 20
		RE_SetColor(colBlackFade);
		SCR_DrawPic(x, y + this->height - OVERLAY_HEIGHT, width, OVERLAY_HEIGHT, *whiteShader);
#if 1
		vec4_t whiteColor = { 1, 1, 1, 1 };
		RE_SetColor(whiteColor);

		const char *szString = this->text.c_str();

#define UFONTSCALE .3

		int offsetY = ((UFONTSCALE / SMALLCHAR_SCALE) * SMALLCHAR_HEIGHT);
		SCR_DrawString(x, y + height - offsetY + 5, 1, UFONTSCALE, whiteColor, szString, NULL, NULL, NULL);
#endif
		vec4_t colWhite = { 1, 1, 1, .15 };
		RE_SetColor(colWhite);

		if (ui_cursor != nullptr && IsColliding(ui_cursor->x, ui_cursor->y)) {
			SCR_DrawPic(x, y, width, height, *whiteShader);
		}
		RE_SetColor(NULL);
	}

	virtual ~UITile() {}
};

class UITextbox : public UIObject {
public:
	bool (*m_OnEnter)(UITextbox *o);

	UITextbox(int a, int b, int c, int d) : UIObject(a, b, c, d) {
		this->classType = UIOT_TEXTBOX;
		m_OnEnter = nullptr;
	}

	void OnEnter() {
		if (this->m_OnEnter == nullptr)
			return;

		if (this->m_OnEnter(this))
			this->text.clear();
	}

	unsigned int GetTextWidth() {
		return this->fontScale * this->text.size();
	}

	virtual ~UITextbox() {}

	void Render() {
		RE_SetColor(this->bgColor);
		SCR_DrawPic(x, y, width, height, *this->shader);
		RE_SetColor(NULL);
		SCR_DrawString(x, y + (SMALLCHAR_HEIGHT * (fontScale / SMALLCHAR_SCALE)), 1, this->fontScale, vColorWhite, this->text.c_str(), NULL, this->text.size(), NULL);
	}
};

class UIMenu {
public:
#ifdef USE_UNIQUE_PTR
	std::vector<std::unique_ptr<UIObject>> items;
#else
	std::vector<UIObject*> items;
#endif

	int x, y, width, height;
	std::string name;
	bool visible;
	bool focused;
	bool bOverrideUI;
	bool bMainHook;
	bool isGL;
	int eName;

	int *hBgShader;
	vec4_t fBgColor;
	cvar_t *showoncvar;

	bool(*m_CallbackKeyEvent)(UIMenu*, int key, int x, int y);

	/* used for main menu */
	int scrollAmount, scrollAmountFeedback, scrollTime;

	static UIMenu *prevFocus;

	UIMenu *get() { //for std::unique_ptr quick change
		return this;
	}

	bool IsOpen() {
		if (this->showoncvar != nullptr) {
			if (!this->showoncvar->integer)
				return false;
		}
		if (!this->visible)
			return false;
		return true;
	}

	UIMenu(int x_, int y_) : 
		items{}, x(x_), y(y_), focused(false), visible(false), hBgShader(whiteShader),
		height(0), width(0), bOverrideUI(false), bMainHook(false), m_CallbackKeyEvent(nullptr),
		scrollAmount(0), scrollAmountFeedback(0), scrollTime(0),
		name("unnamed menu"), isGL(false), eName(0), showoncvar(nullptr)
	{
		Vector4Set(fBgColor, 1, 1, 1, 1);
	}

	void showOnCvar(const char *cvar_name, int default) {
		showoncvar = Cvar_Get(cvar_name, va("%d", default), 0);
	}

	UIMenu(int x_, int y_, int width_, int height_) : UIMenu(x_, y_) {
		width = width_;
		height = height_;
	}

	~UIMenu() {
		//MsgBox("destroyed menu!\n");
#ifndef USE_UNIQUE_PTR
		for (int i = 0; i < items.size(); i++)
			delete items[i];
#endif
	}

	void SetBackgroundColor(float r, float g, float b, float a) {
		fBgColor[0] = r;
		fBgColor[1] = g;
		fBgColor[2] = b;
		fBgColor[3] = a;
	}

	void SetBackgroundColorRGBA(float r, float g, float b, float a) {
		fBgColor[0] = r / 255;
		fBgColor[1] = g / 255;
		fBgColor[2] = b / 255;
		fBgColor[3] = a / 255;
	}

	void SetShader(int *hShader) {
		hBgShader = hShader;
	}

	void SetVisible(bool f) {
		visible = f;
		//for (auto &i : items)
		//i.visible = f;
	}

	void SetFocused(bool f) {
		if (UIMenu::prevFocus != nullptr)
			UIMenu::prevFocus->focused = false;
		UIMenu::prevFocus = this;
		focused = f;
	}

#define IS_COLLIDING(bx, by, bw, bh, cx, cy) \
	(cx >= bx && cx <= bx + bw && cy >= by && cy <= by + bh)	
	//(abs(bx - cx) * 2 < (bw + 5)) && (abs(by - cy) * 2 < (bh + 5))
	
	void OnKeyEvent(int key, int,int);

	bool IsMouseOver() {
		if (ui_cursor == nullptr)
			return false;
		int x_ = ui_cursor->x;
		int y_ = ui_cursor->y;

		if (x_ >= x && x_ <= x + width
			&& y_ >= y && y_ <= y + height)
		{
			return true;
		}
		return false;
	}
#ifdef USE_UNIQUE_PTR
	void AddElement(std::unique_ptr<UIObject>& obj) {
		if (this->isGL)
			obj->isGL = true;
		obj->cParent = this;
		items.push_back(std::move(obj));
	}

	void AddElement(UIObject* obj) {
		this->AddElement(std::unique_ptr<UIObject>(obj));
	}
#else
	void AddElement(UIObject *obj) {
		obj->cParent = this;
		items.push_back(obj);
	}
#endif

	void Open() {
		visible = true;
		focused = true;
	}

	void Close() {
		if (UIMenu::prevFocus == this)
			UIMenu::prevFocus = nullptr;
		visible = false;
		focused = false;
		if (UIObject::prevFocus == nullptr)
			return;
		for (int i = 0; i < items.size(); i++) {
			if (UIObject::prevFocus == items[i].get())
				UIObject::prevFocus = nullptr;
			items[i]->focused = false;
		}
	}

	void Render(bool);
};

class UIFeeder : public UIObject {
public:
	int scrollAmount;

	void *s_Item;
	UIFeeder(int a, int b, int c, int d) : UIObject(a,b,c,d) {
		classType = UIOT_FEEDER;
		shader = whiteShader;
		s_Item = nullptr;
		scrollAmount = 0;
	}

	virtual void Render() {
	}

	virtual unsigned int getSize() {
		return 0;
	}

	virtual unsigned int getStep() {
		return 1;
	}

	virtual ~UIFeeder() {}
};

class UIClientFeeder : public UIFeeder {
public:
	mClient *s_Client;

	UIClientFeeder(int x_,int y_,int w_,int h_) : UIFeeder(x_,y_,w_,h_) {
		classType = UIOT_PLAYERFEEDER;
		s_Client = nullptr;
	}

	virtual ~UIClientFeeder() {}

	unsigned int getSize() {
		return mClients.size();
	}

	void Render() {
		if (ui_cursor == NULL)
			return;
		if (ui_cursor->x < 540)
			return;

		int drawidx = 0;

		vec4_t colBlack = { 0, 0, 0, .5 };

		float *use_color = selected ? vColorSelected : vColorWhite, *txt_color;

		RE_SetColor(colBlack);
		SCR_DrawPic(x, y, width, height, *shader);
		RE_SetColor(NULL);
		float blue_overlay_color[] = { 0, .3, 1, .6 };
		int tX, tY, name_width;
		char *p_name;
		
		bool f = false;

		for (int i = this->scrollAmount; i < mClients.size(); i++) {
			tX = x;
			tY = y + (SMALLCHAR_HEIGHT * drawidx);
			p_name = (char*)mClients[i].lastName.c_str();
			name_width = CG_DrawStrlen(p_name) * SMALLCHAR_WIDTH;
			txt_color = vColorWhite;
			if (keys[K_MOUSE1].down &&
				ui_cursor->x > tX && ui_cursor->x < tX + width
				&& ui_cursor->y > tY && ui_cursor->y < tY + (SMALLCHAR_HEIGHT)) {
				//Com_Printf("selected %s\n", p_name);
				Cvar_Set("cm_pl_selectedid", va("%u", mClients[i].serverid));
				s_Client = &mClients[i];
			}
			if (s_Client == &mClients[i]) {
				txt_color = vColorSelected;
				f = true;
			}
			SCR_DrawString(tX, tY + SMALLCHAR_HEIGHT - 4, 1, SMALLCHAR_SCALE, txt_color, p_name, NULL, NULL, NULL);
			if (s_Client == &mClients[i]) {
				RE_SetColor(blue_overlay_color);
				SCR_DrawPic(tX, tY, width, SMALLCHAR_HEIGHT, *whiteShader);
				RE_SetColor(NULL);
			}

			++drawidx;
		}
		if (!f)
			s_Client = nullptr;
	}
};

class XUI {
public:
#ifdef USE_UNIQUE_PTR
	std::vector<std::unique_ptr<UIMenu>> menus;
	std::vector<std::unique_ptr<UIObject>> objects;
#else
	std::vector<UIMenu*> menus;
	std::vector<UIObject*> objects;
#endif

	XUI() : menus{}, objects{} {
	}
	~XUI() {
		//MsgBox(va("Destroyed XUI menu size = %d, obj size = %d\n", menus.size(), objects.size()));
#ifndef USE_UNIQUE_PTR
		for (int i = 0; i < menus.size(); i++)
			delete menus[i];
#endif
	}
#ifdef USE_UNIQUE_PTR
	UIObject *createObject(int x, int y, int w, int h) {
		std::unique_ptr<UIObject> o(new UIObject(x, y, w, h));
		int idx = objects.size();
		objects.push_back(std::move(o));
		return objects[idx].get();
	}

	template<typename T>
	T* createMenuItem(UIMenu *M, int x, int y, int w, int h) {
		std::unique_ptr<T> i(new T(x, y, w, h));
		size_t q = M->items.size();
		M->AddElement((std::unique_ptr<UIObject>)(std::move(i)));
		return dynamic_cast<T*>(M->items[q].get());
	}

	UIMenu *createMenu(int x, int y, int w, int h) {
		std::unique_ptr<UIMenu> m(new UIMenu(x, y, w, h));
		int idx = menus.size();
		menus.push_back(std::move(m));
		return menus[idx].get();
	}
#else
	UIObject *createObject(int x, int y, int w, int h) {
		UIObject *o = new UIObject(x, y, w, h);
		objects.push_back(o);
		return o;
	}

	template<typename T>
	T* createMenuItem(UIMenu *M, int x, int y, int w, int h) {
		T* i = new T(x, y, w, h);
		M->AddElement(i);
		return i;
	}

	UIMenu *createMenu(int x, int y, int w, int h) {
		UIMenu *m = new UIMenu(x, y, w, h);
		menus.push_back(m);
		return m;
	}
#endif
#ifdef USE_UNIQUE_PTR
	void addMenu(std::unique_ptr<UIMenu> m) {
		this->menus.push_back(std::move(m));
	}
	void addObject(std::unique_ptr<UIObject> o) {
		this->objects.push_back(std::move(o));
	}
#endif
	void addMenu(UIMenu *m) {
#ifdef USE_UNIQUE_PTR
		this->menus.push_back(std::unique_ptr<UIMenu>(m));
#else
		this->menus.push_back(m);
#endif
	}
	void addObject(UIObject *o) {
#ifdef USE_UNIQUE_PTR
		objects.push_back(std::unique_ptr<UIObject>(o));
#else
		objects.push_back(o);
#endif
	}
};

extern XUI *xui;

extern UIMenu *xuim_overlay;
#include "shared.h"
#include "render.h"
#include "client.h"
#include "exmaster_client.h"

qkey_t *keys = (qkey_t*)0x142F780;

static cvar_t *cl_bypassMouseInput = (cvar_t*)0x142F604;
#if 0
static int (QDECL *VM_Call)(int vm, int callnum, ...) = (int(QDECL*)(int, int...))0x460480;

#define uivm 0x161747C
#define cgvm 0x1617348
#define UI_MOUSE_EVENT 4
#define CG_MOUSE_EVENT 7
#define cl_mouseIndex (*(PINT)0x143A958)
PINT cl_mouseDx = (PINT)0x143A948;
PINT cl_mouseDy = (PINT)0x143A950;

void _CL_MouseEvent(int dx, int dy, int time) {
	if (*cls_keyCatchers & KEYCATCH_UI) {

		// NERVE - SMF - if we just want to pass it along to game
		if (cl_bypassMouseInput->integer == 1) {
			cl_mouseDx[cl_mouseIndex] += dx;
			cl_mouseDy[cl_mouseIndex] += dy;
		}
		else {
			VM_Call(uivm, UI_MOUSE_EVENT, dx, dy);
		}
	}
	else if (*cls_keyCatchers & KEYCATCH_CGAME) {
		if (cl_bypassMouseInput->integer == 1) {
			cl_mouseDx[cl_mouseIndex] += dx;
			cl_mouseDy[cl_mouseIndex] += dy;
		}
		else {
			VM_Call(cgvm, CG_MOUSE_EVENT, dx, dy);
		}
	}
	else {
		cl_mouseDx[cl_mouseIndex] += dx;
		cl_mouseDy[cl_mouseIndex] += dy;
	}
}

void __declspec(naked) CL_MouseEvent() {
	__asm {
		push ecx
		push eax
		push 0
		call _CL_MouseEvent
		ret
	}
}
#endif /* cba */

#define KEY_ENTER 13 //KEY_RETURN?
#define KEY_BACKSPACE 8

void CL_CharEvent_(int key) {
	//Com_Printf("Key: %d\n", key);

	if (key == (unsigned char) '`' || key == (unsigned char) '~') {
		return;
	}
	/* some day use the field_t types :D:D:DD but for now custom */
	if (*cls_keyCatchers & KEYCATCH_CONSOLE)
		return;

	if(UIObject::prevFocus != nullptr) {
		UIObject *o = UIObject::prevFocus;
		if (o->focused && o->IsOpen()) {
			if (o->classType == UIOT_TEXTBOX) {
				if (key == KEY_ENTER) {
					UITextbox *t = dynamic_cast<UITextbox*>(o);
					if (t != nullptr)
						t->OnEnter();
				} else if (key == 8) {
					if (o->text.size())
						o->text.pop_back();
				}
				else {
					bool found = false;

					for (int c = ' '; c < '~'; c++) {
						if (c == key) {
							found = true;
							break;
						}
					}

					if (found) {
						int len = (SMALLCHAR_WIDTH * (o->fontScale / SMALLCHAR_SCALE)) * o->text.size() + 1;
						if (len <= o->width)
							o->text.push_back(key);
					}
				}
			}
		}
	}
}

#define CALL_CL_KEYEVENT(key) \
	__asm{push ebx} \
	__asm{mov ebx, 40E200h} \
	__asm{mov eax, key} \
	__asm{call ebx} \
	__asm{pop ebx}

UINT_PTR pcl_charevent = (UINT_PTR)0x40E200;

void __declspec(naked) CL_CharEvent() {
	__asm
	{
		push eax
		call pcl_charevent
		call CL_CharEvent_
		add esp, 4
		retn
	}
}

#define SHIFT_KEY 160
#define SPACE_KEY 32
#define KEY_ESCAPE 27

#define IS_TOGGLING_OVERLAY (keys[SHIFT_KEY].down && keys[SPACE_KEY].repeats <= 1 && keys[SPACE_KEY].down && key == SPACE_KEY)
qkey_t qeys[MAX_KEYS] = { 0 };

//#include "Browser/Browser.h"

void CL_KeyEvent(int key, int down, unsigned int time) {
	call<void*, int, int, unsigned>(0x40DC30, key, down, time);

	if (!key)
		return;

	if (ui_cursor == nullptr)
		return;

	if (xuim_overlay != nullptr && xuim_overlay->IsOpen() && *cls_state == CA_DISCONNECTED) {
#if 0
		Key_SetCatcher(*cls_keyCatchers & ~KEYCATCH_UI);
		Key_SetCatcher(*cls_keyCatchers & ~KEYCATCH_CONSOLE);
#endif
	}
#if 0
	if (IS_TOGGLING_OVERLAY) {
		if (xuim_overlay != nullptr) {
			if (!xuim_overlay->IsOpen())
				xuim_overlay->Open();
			else
				xuim_overlay->Close();
			return;
		}
	}
#endif

	void CG_KeyEvent(int, int, unsigned);
	CG_KeyEvent(key, down, time);

	if (*cls_keyCatchers & KEYCATCH_CONSOLE) {

		if (key == 'a' && keys[K_LCTRL].down) {
			char *consoleBuffer = (char*)0x142F65C;
			if (CopyToClipboard(consoleBuffer));
		}
		return;

	}

	if (key == 171) { //f5
		//GetDefaultBrowser()->RefreshPage(true);
	}
	else if (key == 172) { //f6
		//GetDefaultBrowser()->Screenshot("./browser_shot.jpg");
	}
	else if (key == K_MOUSE1) {
#if 0
		Browser *br = GetDefaultBrowser();

		if (br != nullptr) {
			int mousex = ui_cursor->x;
			int mousey = ui_cursor->y;
			float ratio = (br->width / 800);
			int mouse_b_x = mousex;
			int mouse_b_y = mousey;
			br->Click(mouse_b_x, mouse_b_y);
		}
#endif
	}

	if (!down || !keys[key].down || keys[key].repeats > 1)
		return;

#if 0
	if (key != K_MWHEELDOWN && key != K_MWHEELUP) {
		if (!qeys[key].down) {

			qeys[key].down ^= 1;
			return;
		}
	}
#endif

	if (xui == nullptr)
		return;

	bool bOverrideMenu = false;
	int mousex = ui_cursor->x;
	int mousey = ui_cursor->y;

	for (auto& i : xui->menus) {
		if (!i->IsOpen()) continue;

		if (i->IsMouseOver() && key == K_MOUSE1)
			i->SetFocused(true);

		if (i->focused) {
			if (i->bOverrideUI && !bOverrideMenu) {
#if 0
				Key_SetCatcher(*cls_keyCatchers & ~KEYCATCH_UI);
				Key_SetCatcher(*cls_keyCatchers & ~KEYCATCH_CONSOLE);
#endif
				bOverrideMenu = true;
			}
			//Com_Printf("key event: %d\n", key);
			i->OnKeyEvent(key, mousex, mousey);
		}
	}
	qeys[key].down ^= 1;

	//Com_DPrintf("Key: %lu\n", key); /* __dev__ */
}
#include "shared.h"
#include "render.h"
#include "client.h"
#include "exmaster_client.h"

qkey_t* keys = (qkey_t*)0x142F780;

static cvar_t* cl_bypassMouseInput = (cvar_t*)0x142F604;

#define KEY_ENTER 13 //KEY_RETURN?
#define KEY_BACKSPACE 8

void CL_CharEvent_(int key) {
	if (key == (unsigned char)'`' || key == (unsigned char)'~') {
		return;
	}
	if (*cls_keyCatchers & KEYCATCH_CONSOLE) // some day use the field_t types :D:D:DD but for now custom (c) php
		return;
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

void CL_KeyEvent(int key, int down, unsigned int time) {
	call<void*, int, int, unsigned>(0x40DC30, key, down, time);

	if (!key)
		return;

	if (ui_cursor == nullptr)
		return;

	void CG_KeyEvent(int, int, unsigned);
	CG_KeyEvent(key, down, time);

	if (*cls_keyCatchers & KEYCATCH_CONSOLE) {

		if (key == 'a' && keys[K_LCTRL].down) {
			char* consoleBuffer = (char*)0x142F65C;
			if (CopyToClipboard(consoleBuffer));
		}
		return;

	}

	if (!down || !keys[key].down || keys[key].repeats > 1)
		return;
}

UINT_PTR pfield_charevent_return = (UINT_PTR)0x40CB77;
UINT_PTR pfield_charevent_continue = (UINT_PTR)0x40CB23;

__declspec(naked) void Field_CharEvent_IgnoreTilde()
{
	__asm
	{
		cmp ebx, 20h
		jge check
		jmp pfield_charevent_return

		check :
		cmp ebx, 126
			jl checked
			jmp pfield_charevent_return

			checked :
		jmp pfield_charevent_continue
	}
}

// cmp ebx, 20h is 3 bytes, we need 5 for a jmp...
// jl ... is 2 bytes 7c54 (assuming when subtracing the addresses)
// so it works out
// - Richard
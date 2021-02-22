#pragma once

#define K_MWHEELDOWN 205
#define K_MWHEELUP 206
#define K_MOUSE1 200
#define K_MOUSE2 201
#define K_LCTRL 159

typedef struct {
	int x, y;
} cursorPositionInfo_t;
extern cursorPositionInfo_t *ui_cursor;

#define KEYCATCH_CONSOLE        0x0001
#define KEYCATCH_UI             0x0002
#define KEYCATCH_MESSAGE        0x0004
#define KEYCATCH_CGAME          0x0008
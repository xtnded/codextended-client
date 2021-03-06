#include "shared.h"
#include "resource.h"

static HBITMAP hBitmap = NULL;
extern HINSTANCE hInstance;
extern HMODULE hModule;

LRESULT CALLBACK ConsoleWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;

	switch (message) {
		case WM_CREATE:
			hBitmap = (HBITMAP)LoadImageA((HINSTANCE)hModule, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_SHARED | LR_COPYFROMRESOURCE);
		break;
		case WM_PAINT:
			PAINTSTRUCT 	ps;
			HDC 			hdc;
			BITMAP 			bitmap;
			HDC 			hdcMem;
			HGDIOBJ 		oldBitmap;

			hdc = BeginPaint(hWnd, &ps);

			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hBitmap);

			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);

			EndPaint(hWnd, &ps);
		break;
		case WM_DESTROY:
			DeleteObject(hBitmap);
		break;
	}
	LRESULT CALLBACK ret = ((LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM))0x465E80)(hWnd, message, wParam, lParam);

	return ret;
}

void Con_DrawSolidConsole(float frac) {
	extern cvar_t *cl_console_fraction;
	((void(*)(float))0x409F30)(frac * cl_console_fraction->value);
}
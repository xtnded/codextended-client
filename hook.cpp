#include "stdafx.h"
#include "shared.h"
#include "client.h"

//0046319B E8 10 B1 FA FF                                      call    sub_40E2B0
void sub_40E2B0() {
	void(*o)();
	*(UINT32*)&o = 0x40E2B0;
	o();


	void Sys_Unload();
	Sys_Unload();
}

void Main_UnprotectModule(HMODULE hModule)
{
	PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hModule + header->e_lfanew);

	// unprotect the entire PE image
	SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
	DWORD oldProtect;
	VirtualProtect((LPVOID)hModule, size, PAGE_EXECUTE_READWRITE, &oldProtect);
}

bool apply_hooks() {
	HMODULE hModule;
	if (SUCCEEDED(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)apply_hooks, &hModule)))
	{
		Main_UnprotectModule(hModule);
	}


	void patch_opcode_loadlibrary();
	patch_opcode_loadlibrary();
#if 1
	if (codversion == CODUO_51) {
		XUNLOCK((void*)0x4500FB, 5);
		*(UINT32*)(0x4500FB + 1) = 0x17f;
		//patch info_setvalueforkey q3infoboom
	}
#endif
	
	if (codversion != COD_1)
		return true;

	__call(0x46319B, (int)sub_40E2B0); //cleanup exit

	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	__call(0x528948, (int)WinMain);

	//__nop(0x437B39, 5); //call NET_Init we're gonna call it a bit sooner cuz we need it ;)

	void NET_Init();
	__call(0x437B39, (int)NET_Init);

#if 1
	void Con_DrawSolidConsole(float);
	__call(0x40A21D, (int)Con_DrawSolidConsole);
	__call(0x40A234, (int)Con_DrawSolidConsole);
	__call(0x40A257, (int)Con_DrawSolidConsole);
#endif

	void CL_Connect_f();
	XUNLOCK((void*)0x41269B, 5);
	*(UINT32*)(0x41269B + 1) = (int)CL_Connect_f;

#if 0 //crashes on cmd quit
	void CL_ShutdownUI();
	__call(0x40EE30 + 0x6, (int)CL_ShutdownUI);
	__call(0x40FBE0 + 0xBB, (int)CL_ShutdownUI);
	__call(0x40FBE0 + 0x10F, (int)CL_ShutdownUI);
	__call(0x4127F0, (int)CL_ShutdownUI);
	__call(0x431E00 + 0xE3, (int)CL_ShutdownUI);
	__call(0x432140 + 0x5, (int)CL_ShutdownUI);
	__call(0x4358A0 + 0xF, (int)CL_ShutdownUI);
	__call(0x4358A0 + 0x4A, (int)CL_ShutdownUI);
	__call(0x458760 + 0x10A, (int)CL_ShutdownUI);
	__call(0x458760 + 0x152, (int)CL_ShutdownUI);
	__call(0x462B20 + 0x3A, (int)CL_ShutdownUI);
#endif

	void RB_ExecuteRenderCommands();
#if 0
	//__jmp(0x4D8AB0, (int)RB_ExecuteRenderCommands);
	__call(0x004B4A17, (int)RB_ExecuteRenderCommands		);
	__call(0x4D6DB0 + 0x37, (int)RB_ExecuteRenderCommands	);
	__call(0x4D9FA0 + 0x4E, (int)RB_ExecuteRenderCommands	);
	__call(0x4DDBA0 + 0x41, (int)RB_ExecuteRenderCommands	);
	__call(0x4DDBF0 + 0x38, (int)RB_ExecuteRenderCommands	);
	__call(0x004DE50C, (int)RB_ExecuteRenderCommands		);
	__call(0x4FC5C0 + 0xee, (int)RB_ExecuteRenderCommands	);
	__call(0x004FC93B, (int)RB_ExecuteRenderCommands		);
	__call(0x005035E8, (int)RB_ExecuteRenderCommands		);
#endif

	unlock_client_structure(); /* make some client cls_ structure members writeable etc */

	//0041627B 10C                 call    sub_410240
	//__call(0x41627B, (int)CL_InitDownloads);
	void CL_NextDownload();
	//__call(0x410316, (int)CL_NextDownload);
	__jmp(0x410190, (int)CL_NextDownload);

	void CL_Frame(int msec);
	__call(0x43822C, (int)CL_Frame);

#if 1
	LRESULT CALLBACK ConsoleWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	XUNLOCK((void*)0x466414, 4);
	*(int*)0x466414 = (int)ConsoleWndProc;
#endif

	void CL_CharEvent();
	__call(0x436643, (int)CL_CharEvent);

	void CL_KeyEvent(int, int, unsigned);
	__call(0x436635, (int)CL_KeyEvent);
	//__call(0x40E27D, (int)CL_KeyEvent); //called when cleared
	void CL_MouseEvent();
	//__call(0x436657, (int)CL_MouseEvent);

#if 1
	void CL_PacketEvent();
	__call(0x436794, (int)CL_PacketEvent);
	__call(0x436743, (int)CL_PacketEvent);
#endif
	void CL_Init();
	__call(0x437B4B, (int)CL_Init);
	__call(0x438178, (int)CL_Init);

	void SCR_DrawScreenField(stereoFrame_t stereoFrame);
	__call(0x41703A, (int)SCR_DrawScreenField);
	__call(0x417048, (int)SCR_DrawScreenField);
	
	char* __cdecl CL_ClearHostname(char*, char*, size_t);
    __call(0x412A2C, (int)CL_ClearHostname);

#if 1

	void DrawTris(void*);
	__call(0x5028FD, (int)DrawTris);
	__nop(0x5028F6, 2);
	__nop(0x5028EE, 2); //if(r_showtris->integer and some other check
#endif

	void RB_ShowImages();
	__call(0x4D87F5, (int)RB_ShowImages);
	__nop(0x4D87F0, 5); //cmp and jz for r_showImages->integer

#if 1 //crashes
	void __stdcall RB_BeginSurface();
	__call(0x4D4A2C, (int)RB_BeginSurface);
	__call(0x4D6886, (int)RB_BeginSurface);
	__call(0x4D740B, (int)RB_BeginSurface);
	__call(0x4D7650, (int)RB_BeginSurface);
	__call(0x4D7852, (int)RB_BeginSurface);
	__call(0x4D7B20, (int)RB_BeginSurface);
	__call(0x4D8448, (int)RB_BeginSurface);
	__call(0x4D9588, (int)RB_BeginSurface);
	__call(0x4E0492, (int)RB_BeginSurface);
	__call(0x4E810E, (int)RB_BeginSurface);
	__call(0x4E847C, (int)RB_BeginSurface);
	__call(0x4E84FE, (int)RB_BeginSurface);
	__call(0x4E860B, (int)RB_BeginSurface);
	__call(0x50F9E2, (int)RB_BeginSurface);
	__jmp(0x50FA0F , (int)RB_BeginSurface);
	__call(0x50FA72, (int)RB_BeginSurface);
	__call(0x50FE75, (int)RB_BeginSurface);
	__call(0x511067, (int)RB_BeginSurface);
	__call(0x511D85, (int)RB_BeginSurface);
	__call(0x51269B, (int)RB_BeginSurface);
#endif

	void* ri_Hunk_AllocAlign(int size);
	XUNLOCK((void*)0x4FD6AF, 6);
	*(BYTE*)0x4FD6AF = 0xe8;
	__call(0x4FD6AF, (int)ri_Hunk_AllocAlign); //cannot call since it's 6 opcodes
	*(BYTE*)(0x4FD6AF + 5) = 0x90;

	void ScanAndLoadShaderFiles(void);
	__call(0x4FDB74, (int)ScanAndLoadShaderFiles);

	void AddCustomShader_w();
	//004FD735   > 8B4424 1C      MOV EAX, DWORD PTR SS : [ESP + 1C]
	//004FD739   . 50             PUSH EAX
	//004FD73A   . FF15 78896D01  CALL DWORD PTR DS:[16D8978]              ;  _CoDMP.0042B710
	__jmp(0x4FD735, (int)AddCustomShader_w);

#if 0

	void GL_Bind();
	__call(0x004D6E76, (int)GL_Bind);
	__call(0x004D729D, (int)GL_Bind);
	__call(0x004D83D4, (int)GL_Bind);
	__call(0x004D8648, (int)GL_Bind);
	__call(0x004D88B9, (int)GL_Bind);
	__call(0x004D992A, (int)GL_Bind);
	__call(0x004DFDEC, (int)GL_Bind);
	__call(0x004DFFC5, (int)GL_Bind);
	__call(0x4E6E28, (int)GL_Bind);
	__call(0x004EA5BC, (int)GL_Bind);
	__call(0x4EC65C, (int)GL_Bind);
	__call(0x004FE1B3, (int)GL_Bind);
	__call(0x004FF057, (int)GL_Bind);
	__call(0x004FF321, (int)GL_Bind);
	__call(0x5009A6, (int)GL_Bind);
	__call(0x00505936, (int)GL_Bind);
	__call(0x00505B8A, (int)GL_Bind);
	__call(0x005064DD, (int)GL_Bind);
	__call(0x0050696D, (int)GL_Bind);
	__call(0x00507A08, (int)GL_Bind);
	__call(0x0050F05B, (int)GL_Bind);
	__call(0x0050F124, (int)GL_Bind);
	__call(0x0050F1FB, (int)GL_Bind);
	__call(0x0050F2A5, (int)GL_Bind);
	__call(0x00510920, (int)GL_Bind);
	__call(0x0051276C, (int)GL_Bind);
	__call(0x0051301A, (int)GL_Bind);
	__call(0x0051319A, (int)GL_Bind);
#endif

	return true;
}
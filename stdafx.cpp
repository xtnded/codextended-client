#include "stdafx.h"

void Q_strcat(char *dest, int size, const char *src);
void Q_strncpyz(char *dest, const char *src, int destsize);

#include <ShlObj.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "Comdlg32.lib")
#include "Commdlg.h"

int codversion = COD_UNKNOWN;

std::string file_get_contents(const char *fn) {
	FILE *fp = NULL;

	fp = fopen(fn, "r");

	if (fp == NULL)
		return "";

	char *buf = NULL;
	size_t fs = 0;
	fseek(fp, 0, SEEK_END);
	fs = ftell(fp);
	rewind(fp);

	buf = (char*)malloc(fs);
	if (fread(buf, 1, fs, fp) != fs) {
		fclose(fp);
		return "";
	}
	std::string res(buf);
	free(buf);
	fclose(fp);
	return res;
}

std::string GetOpenFileNameS(HWND owner)
{
	char buffer[MAX_PATH] = "";

	OPENFILENAME ofn = { 0 };

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = "JPG\0*.jpg\0All Files\0*\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = buffer;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn))
		return "";

	return buffer;
}

std::string GetLastErrorAsString()
{
	//Get the error message, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0)
		return "";

	LPSTR messageBuffer = NULL;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	std::string message(messageBuffer, size);

	//Free the buffer.
	LocalFree(messageBuffer);

	return message;
}

int Sys_GetModulePathInfo(HMODULE module, char **path, char **filename, char **extension) {
	int sep = '/';
	static char szFileName[MAX_PATH + 1];
	if (path)
		*path = NULL;
	if (filename)
		*filename = NULL;
	if (extension)
		*extension = NULL;

	GetModuleFileNameA(module, szFileName, MAX_PATH);

	char *fn = strrchr(szFileName, sep);
	if (fn == nullptr) {
		sep = '\\';
		fn = strrchr(szFileName, sep);
	}
	if (fn != NULL) {
		*fn++ = 0;

		char *ext = strrchr(fn, '.');

		if (ext != NULL) {
			if (fn != ext) {
				if (extension)
					*ext++ = 0;
				if (path)
					*path = szFileName;
				if (filename)
					*filename = fn;
				if (extension)
					*extension = ext;
			}
		}
	}
	return sep;
}

const char *Sys_GetAppDataFolder(char *szPath, int dwLen, bool create) {
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, SHGFP_TYPE_CURRENT, szPath))) {
		Q_strncpyz(szPath, szPath, dwLen);
		Q_strcat(szPath, dwLen, "\\CoDExtended");

		if (!create)
			return szPath;

		if (!PathFileExists(szPath)) {
			if (ERROR_SUCCESS != SHCreateDirectoryEx(NULL, szPath, NULL)) {
				return NULL;
			}

		}
	}
	return szPath;
}
#include "shared.h"
#include "dl_public.h"
#include "client.h"
#pragma comment(lib, "libs/libcurl/libcurl.lib")
#include "libs/libcurl/curl.h"
#include <iostream>
#include "version.h"

#define APP_NAME        "ID_DOWNLOAD"
#define APP_VERSION     "2.0"

// initialize once
static int dl_initialized = 0;
static CURLM *dl_multi = NULL;
static CURL *dl_request = NULL;
FILE *dl_file = NULL;

bool clc_bWWWDl = false;

/* simple implem */

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int create_progress_download(const char *url, FILE *fp, int (*progress_callback)(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)) {
	if (fp == nullptr)
		return -1;

	CURL *curl = nullptr;
	CURLcode res;

	curl = curl_easy_init();

	if (curl == nullptr)
		return -1;

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
	res = curl_easy_perform(curl);
	//if (res != CURLE_OK && CURLE_ABORTED_BY_CALLBACK)
		//MsgBox(curl_easy_strerror(res));

	curl_easy_cleanup(curl);
	fclose(fp);

	return res;
}

bool simple_download(const char *url, const char *local) {
	CURL *curl = NULL;
	FILE *fp = NULL;
	CURLcode res;

	curl = curl_easy_init();

	if (curl != NULL) {
		fp = fopen(local, "wb");

		if (!fp) {
			return false;
		}
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			return false;
		}
		curl_easy_cleanup(curl);
		fclose(fp);
	}
	return true;
}

/* end */

/*
** Write to file
*/
static size_t DL_cb_FWriteFile(void *ptr, size_t size, size_t nmemb, void *stream) {
	FILE *file = (FILE*)stream;
	return fwrite(ptr, size, nmemb, file);
}

/*
** Print progress
*/
static int DL_cb_Progress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
	/* cl_downloadSize and cl_downloadTime are set by the Q3 protocol...
	and it would probably be expensive to verify them here.   -zinx */

	Cvar_Set("cl_downloadSize", va("%f", (float)dltotal));
	Cvar_Set("cl_downloadCount", va("%f", (float)dlnow));
	return 0;
}

void DL_InitDownload() {
	if (dl_initialized) {
		return;
	}

	/* Make sure curl has initialized, so the cleanup doesn't get confused */
	curl_global_init(CURL_GLOBAL_ALL);

	dl_multi = curl_multi_init();
	Com_Printf("Client download subsystem initialized\n");
	dl_initialized = 1;
}

/*
================
DL_Shutdown

================
*/
void DL_Shutdown() {
	if (!dl_initialized) {
		return;
	}

	curl_multi_cleanup(dl_multi);
	dl_multi = NULL;

	curl_global_cleanup();
	dl_initialized = 0;
}

#define LOCAL_DL_PATH "dl.tmp"

char localDownloadName[MAX_PATH];

int DL_BeginDownload(const char *localName, const char *remoteName, int debug) {
	char referer[MAX_STRING_CHARS + 5 /*"ET://"*/];
	if (dl_request) {
		Com_Printf("ERROR: DL_BeginDownload called with a download request already active\n"); \
			return 0;
	}

	if (!localName || !remoteName) {
		Com_DPrintf("Empty download URL or empty local file name\n");
		return 0;
	}

	_snprintf(localDownloadName, MAX_PATH - 1, "%s", localName);

	FS_CreatePath(LOCAL_DL_PATH);
	dl_file = fopen(LOCAL_DL_PATH, "wb+");
	if (!dl_file) {
		Com_Printf("ERROR: DL_BeginDownload unable to open '%s' for writing\n", LOCAL_DL_PATH);
		return 0;
	}

	DL_InitDownload();

	/* ET://ip:port */
	/*
	strcpy( referer, "ET://" );
	Q_strncpyz( referer + 5, Cvar_VariableString( "cl_currentServerIP" ), MAX_STRING_CHARS );
	*/

	dl_request = curl_easy_init();
	curl_easy_setopt(dl_request, CURLOPT_USERAGENT, va("%s %s", APP_NAME "/" APP_VERSION, curl_version()));
	//curl_easy_setopt( dl_request, CURLOPT_REFERER, referer );
	curl_easy_setopt(dl_request, CURLOPT_URL, remoteName);
	curl_easy_setopt(dl_request, CURLOPT_WRITEFUNCTION, DL_cb_FWriteFile);
	curl_easy_setopt(dl_request, CURLOPT_WRITEDATA, (void*)dl_file);
	curl_easy_setopt(dl_request, CURLOPT_PROGRESSFUNCTION, DL_cb_Progress);
	curl_easy_setopt(dl_request, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(dl_request, CURLOPT_FAILONERROR, 1);

	curl_multi_add_handle(dl_multi, dl_request);

	Cvar_Set("cl_downloadName", va("        %s", (char*)remoteName)); //spaces so whole link is visible now
	Cvar_Set("dlname_error", (char*)remoteName);
	return 1;
}

// (maybe this should be CL_DL_DownloadLoop)
dlStatus_t DL_DownloadLoop() {
	CURLMcode status;
	CURLMsg *msg;
	int dls = 0;
	const char *err = NULL;

	if (!dl_request) {
		Com_DPrintf("DL_DownloadLoop: unexpected call with dl_request == NULL\n");
		return DL_DONE;
	}

	if (*cls_state != CA_CONNECTING && *cls_state != CA_CHALLENGING && *cls_state != CA_CONNECTED) {
		curl_multi_remove_handle(dl_multi, dl_request);
		curl_easy_cleanup(dl_request);
		fclose(dl_file);
		dl_file = NULL;
		dl_request = NULL;
		Cvar_Set("ui_dl_running", "0");
		return DL_DISCONNECTED;
	}

	if ((status = curl_multi_perform(dl_multi, &dls)) == CURLM_CALL_MULTI_PERFORM && dls) {
		return DL_CONTINUE;
	}

	while ((msg = curl_multi_info_read(dl_multi, &dls)) && msg->easy_handle != dl_request)
		;

	if (!msg || msg->msg != CURLMSG_DONE) {
		return DL_CONTINUE;
	}

	if (msg->data.result != CURLE_OK) {
		err = curl_easy_strerror(msg->data.result);
	}
	else {
		err = NULL;
	}

	curl_multi_remove_handle(dl_multi, dl_request);
	curl_easy_cleanup(dl_request);
	fclose(dl_file);
	dl_file = NULL;

	dl_request = NULL;

	Cvar_Set("ui_dl_running", "0");

	if (err) {
		Com_DPrintf("DL_DownloadLoop: request terminated with failure status '%s'\n", err);
		return DL_FAILED;
	}

	if (!MoveFileA(LOCAL_DL_PATH, localDownloadName)) {
		Com_Printf("DL_DownloadFinished: failed to move temporary storage file to '%s'\n", localDownloadName);
	}

	*localDownloadName = '\0';
	((void(*)())0x40F640)(); //CL_Reconnect_f
	return DL_DONE;
}

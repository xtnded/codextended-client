#include "Browser.h"

#include "../shared.h"

#include "AwesomiumSurface.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>
#include <vector>
#include <gl/gl.h>

#include "method_dispatcher.h"

#if defined(GL_BGRA_EXT) && !defined(GL_BGRA)
#define GL_BGRA GL_BGRA_EXT
#endif

Browser *aws_browser;

static void __browser_goto() {

	if (aws_browser == nullptr) {
		Com_Printf("browser is nullptr\n");
		return;
	}

	char *url = Cmd_Argv(1);

	if (!strlen(url)) {
		Com_Printf("empty url m8\n");
		return;
	}


	if (aws_browser->view == nullptr) {
		Com_Printf("browser view is nullptr\n");
		return;
	}

	Com_Printf("Going to '%s'\n", url);

	aws_browser->Goto(url);

}

Browser::Browser() :
	mouseX(0), mouseY(0)
{
	method_dispatcher = nullptr;
	Awesomium::WebCore *_core;
	core = _core = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	csf = new GLTextureSurfaceFactory;
	_core->set_surface_factory(reinterpret_cast<GLTextureSurfaceFactory*>(csf));
	CreateView(640, 480);
	/* subject to change due to width, height */

	Cmd_AddCommand("browser_goto", __browser_goto);
}

Browser::~Browser() {
	Cmd_RemoveCommand("browser_goto");
	DestroyView();
	delete csf;
	reinterpret_cast<Awesomium::WebCore*>(core)->Shutdown();
}


class JSFunctions {
public:
	void Print(Awesomium::WebView* caller,
		const Awesomium::JSArray& args) {

		if (args.size() == 0)
			return;

		char string[1024] = { 0 };
		args[0].ToString().ToUTF8(string, sizeof(string) - 1);
		Com_Printf(string);

	}
};

void Browser::AddJSFunctions() {
	method_dispatcher = new MethodDispatcher();

	Awesomium::WebView *view_ = reinterpret_cast<Awesomium::WebView*>(view);

	MethodDispatcher *md = reinterpret_cast<MethodDispatcher*>(method_dispatcher);

	js_functions = new JSFunctions();
	Awesomium::JSValue result = view_->CreateGlobalJavascriptObject(Awesomium::WSLit("COD"));
#if 0
	if (result.IsObject()) {
		// Bind our custom methods to it.
		Awesomium::JSObject& app_object = result.ToObject();
		md->Bind(app_object,
			Awesomium::WSLit("Print"),
			JSDelegate(reinterpret_cast<JSFunctions*>(js_functions), &JSFunctions::Print));
	}

#endif
	// Bind our method dispatcher to the WebView
	view_->set_js_method_handler(md);

	/* using custom js blanks out awesomium for some reason */
	//view_->ExecuteJavascript(Awesomium::WSLit("document.onmousedown=function(){document.write('HAHAHAHA');}"), Awesomium::WSLit(""));
}

void Browser::CreateView(int w, int h) {
	this->width = w;
	this->height = h;
	Awesomium::WebView *view_;
	view = view_ = reinterpret_cast<Awesomium::WebCore*>(core)->CreateWebView(w, h, 0, Awesomium::kWebViewType_Offscreen);

	/* using custom js blanks out awesomium for some reason */

	//this->AddJSFunctions();

	Awesomium::WebURL url(Awesomium::WSLit("http://xtnded.org/ui"));
	view_->LoadURL(url);
	view_->SetTransparent(true);
}

void Browser::Click(int x, int y) {
	if (view == nullptr)
		return;
	Awesomium::WebView *_view = reinterpret_cast<Awesomium::WebView*>(view);

	_view->InjectMouseMove(x, y);
	_view->InjectMouseDown(Awesomium::MouseButton::kMouseButton_Left);
	_view->InjectMouseUp(Awesomium::MouseButton::kMouseButton_Left);
}

void Browser::RefreshPage(bool ignore_cache) {

	reinterpret_cast<Awesomium::WebView*>(view)->Reload(ignore_cache);
}

void Browser::Resize(int w, int h) {
	reinterpret_cast<Awesomium::WebView*>(view)->Resize(w, h);
}

void Browser::DestroyView() {
	if (method_dispatcher != nullptr) {
		delete js_functions;
		js_functions = nullptr;
		delete method_dispatcher;
		method_dispatcher = nullptr;
	}
	reinterpret_cast<Awesomium::WebView*>(view)->Destroy();
}

unsigned int Browser::GetTextureID() {
	if (view == nullptr)
		return 0;
	GLTextureSurface *surface = (GLTextureSurface*)reinterpret_cast<Awesomium::WebView*>(view)->surface();
	if (surface == nullptr)
		return 0;
	return surface->GetTexture();
}

void Browser::Bind() {

	if (view == nullptr)
		return;
	GLTextureSurface *surface = (GLTextureSurface*)reinterpret_cast<Awesomium::WebView*>(view)->surface();
	if (surface != 0)
		glBindTexture(GL_TEXTURE_2D, surface->GetTexture());
}

void Browser::Update() {


#if 0
	if (x_browser_width->modified || x_browser_height->modified)
		Resize(x_browser_width->integer, x_browser_height->integer);
#endif

	reinterpret_cast<Awesomium::WebCore*>(core)->Update();
#if 0
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
	if (view != NULL) {
		Awesomium::BitmapSurface *surface = (Awesomium::BitmapSurface*)view->surface();
		if (surface != 0) {
			int w = surface->width();
			int h = surface->height();

			unsigned char *buffer = new unsigned char[w * h * 4];
			surface->CopyTo(buffer, w * 4, 4, false, false);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);
			surface->Paint(
				delete[] buffer;
		}
	}
#endif


#if 0
	Awesomium::WebView *_view;
	if (view != nullptr) {
		_view = reinterpret_cast<Awesomium::WebView*>(view);

		if (_view->IsLoading())
			return;

		int *ui_get_mouse_coords();

		int *mousepos = ui_get_mouse_coords();

		if (mousepos != NULL) {

			if (mouseX != mousepos[0] || mouseY != mousepos[1]) {
				_view->InjectMouseMove(mouseX, mouseY);
				mouseX = mousepos[0];
				mouseY = mousepos[1];
			}
		}
	}

#endif
}

void Browser::Goto(const char *uri) {

	Awesomium::WebURL url(Awesomium::WSLit(uri));
	if (this->view != nullptr)
		reinterpret_cast<Awesomium::WebView*>(this->view)->LoadURL(url);
}

bool Browser::Screenshot(const char *outfile) {
	if (this->view == nullptr)
		return false;

	Awesomium::WebView *view_ = reinterpret_cast<Awesomium::WebView*>(view);

	if (view_->IsLoading()) {
		Com_Printf("The page is still loading.");
		return false;
	}

	Awesomium::BitmapSurface *surface = (Awesomium::BitmapSurface*)view_->surface();

	if (surface != 0) {
		surface->SaveToJPEG(Awesomium::WSLit(outfile));
	}
}

//#define AWS_PACKAGE_URL "https://www.dropbox.com/s/t5bfyt3tne7xf4h/awesomium_bin_1_7_5_0.zip?dl=1"
//#define AWS_PACKAGE_URL "http://cod1.eu/xtnded/dl/awesomium_bin_1_7_5_0.zip"

int AWS_Check() {
	HMODULE lib = LoadLibraryA("awesomium.dll");

	if (lib != NULL) {
		FreeLibrary(lib);
		return 1;
	}
#if 0
	strcpy(AWS_PATH, szAppData);

	PathAppend(AWS_PATH, "aws.zip");

	if (fexists(AWS_PATH))
		goto skip_dl;

	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl) {
		FILE *fp = fopen(AWS_PATH, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, AWS_PACKAGE_URL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}

	if (res != CURLE_OK)
		ERR(va("cURL Error: %s", curl_easy_strerror(res)))

		skip_dl:
	/*
	UINT crc = 0;

	if(!crc32.FileCRC( AWS_PATH, &crc ))
	ERR("CRC32 failed.")

	if( crc != AWS_CRC )
	ERR("CRC32 mismatch, please download the latest CoDExtended client from " CODSITE)
	*/

	HZIP hz = OpenZip(AWS_PATH, 0);
	ZIPENTRY ze;
	GetZipItem(hz, -1, &ze);
	for (int i = 0; i < ze.index; i++) {
		ZIPENTRY zipentry;
		GetZipItem(hz, i, &zipentry);
		//MessageBox(0,zipentry.name,__TITLE,0);
		UnzipItem(hz, i, zipentry.name);
	}
	CloseZip(hz);
#endif
	return 0;
}

Browser *CreateDefaultBrowser() {
	if (aws_browser != nullptr) {
		return aws_browser;
	}

	aws_browser = new Browser();
	return aws_browser;
}

void DestroyDefaultBrowser() {
	if (aws_browser == nullptr)
		return;
	delete aws_browser;
	aws_browser = nullptr;
}

Browser *GetDefaultBrowser() {
	return aws_browser;
}
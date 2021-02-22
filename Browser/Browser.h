#pragma once

#define BROWSER_WIDTH_DEFAULT 800
#define BROWSER_HEIGHT_DEFAULT 600

class Browser {
public:
	int mouseX, mouseY;

	int width, height;
	/*Awesomium::WebView*/void *view;
	/*Awesomium::WebCore*/void *core;
	/*GLTextureSurfaceFactory*/void *csf;
	Browser();

	~Browser();

	virtual void CreateView(int, int);
	virtual void Resize(int, int);
	virtual void DestroyView();
	virtual void Update();
	virtual void Bind();
	virtual void Goto(const char *);
	virtual bool Screenshot(const char*);

	unsigned int GetTextureID();

	void RefreshPage(bool);

	void Click(int, int);

	void AddJSFunctions();

	void *method_dispatcher, *js_functions;

};

extern Browser *aws_browser;

Browser *CreateDefaultBrowser();
void DestroyDefaultBrowser();
Browser *GetDefaultBrowser();
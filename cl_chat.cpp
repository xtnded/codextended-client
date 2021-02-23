#include "shared.h"
#include "render.h"
#include "client.h"

#define GCHAT_BASE_X 50
#define GCHAT_BASE_Y 20
#define GCHAT_FONT_TYPE 2

static const vec4_t gChatColor = {1,1,1,1};

struct chatmsg {
	std::string name;
	std::string message;
	time_t time;
	float opacity;
	int clearTimer;
};

#define MAX_DISPLAY_MSG 15

class UIGlobalChatMessageWindow : public UIObject {
public:

	std::vector<chatmsg> messages;

	UIGlobalChatMessageWindow(int a, int b, int c, int d) : UIObject(a, b, c, d) {
		classType = UIOT_UIGlobalChatMessageWindow;
		shader = whiteShader;
	}

	virtual void Render() {

		vec4_t bg_color_lower = { 0, 0, 0, .5 };
		vec4_t bg_color = { 0, 0, 0, .85 };
		RE_SetColor(bg_color);
		SCR_DrawPic(x, y, width, height, *whiteShader);
		RE_SetColor(NULL);

		const char *sMessage, *sName;
		int name_len, msg_count = 0;

		time_t curTime = time(NULL);
		vec4_t per_color = { gChatColor[0], gChatColor[1], gChatColor[2], 1 };

		static bool reset_other_faders = false;
		int faders = 0;

		for (std::vector<chatmsg>::iterator it = messages.begin(); it != messages.end();) {
			name_len = 0;
			sMessage = it->message.c_str();
			per_color[3] = it->opacity;

			if (it->name.size() > 0) {
				//sName = va("(difftime = %f and %d) %s: ", difftime(curTime, it->time), *cls_realtime - it->clearTimer, it->name.c_str());
				sName = va("%s: ", it->name.c_str());
				name_len = SMALLCHAR_WIDTH * CG_DrawStrlen(sName);
				SCR_DrawString(x, y + SMALLCHAR_HEIGHT * (msg_count+1), GCHAT_FONT_TYPE, .3, (float*)per_color, sName, NULL, NULL, NULL);
			}
			SCR_DrawString(x + name_len, y + SMALLCHAR_HEIGHT * (msg_count+1), GCHAT_FONT_TYPE, .3, (float*)per_color, sMessage, NULL, NULL, NULL);

			msg_count++;

			if (difftime(curTime, it->time) >= 1 && ((messages.size() > MAX_DISPLAY_MSG && !reset_other_faders) || messages.size() - faders > MAX_DISPLAY_MSG)) {
				if (!it->clearTimer) {
					it->clearTimer = *cls_realtime;
					reset_other_faders = true;
				}
			}

			if (it->clearTimer) {
				if (*cls_realtime - it->clearTimer > 500)
					it->opacity -= 0.007f;
				faders++;
			}

			if (it->opacity <= 0) {
				reset_other_faders = false;
				it = messages.erase(it);
				continue;
			}

			++it;
		}
	}

	virtual ~UIGlobalChatMessageWindow() {}
};

UIGlobalChatMessageWindow *gwindow;

bool xui_txt_box_OnEnter(UITextbox *o) {
	
	void Enc_SendTalkMessage(const char *chatmsg);
	Enc_SendTalkMessage(o->text.c_str());

	return true;
}

void CM_CreateWindow(UIMenu *m) {
	int X_POS = 0;
	int X_WIDTH = 640;
	extern bool bSteamAvailable;
	if (!bSteamAvailable) {
		X_POS = 105;
	}
	gwindow = xui->createMenuItem<UIGlobalChatMessageWindow>(m, X_POS, 0, X_WIDTH, 430);
	UITextbox *txt_box = xui->createMenuItem<UITextbox>(m, X_POS, 440, 200, 30);
	txt_box->SetBackgroundColor(.7, .7, .7, 1);
	txt_box->m_OnEnter = xui_txt_box_OnEnter;
}

void CM_ReceiveHandler(const char *name, const char *message) {
	//if (gChatMessages.size() > 10)
		//gChatMessages.clear();

	chatmsg msg;
	msg.message = message;
	if (name != NULL) //it's a global broadcast
		msg.name = name;
	msg.time = time(NULL);
	msg.opacity = 1;
	msg.clearTimer = 0;
	gwindow->messages.push_back(msg);
}
#include "shared.h"
#include "exmaster_client.h"

std::vector<mClient> mClients;

mClient::mClient(unsigned int _id, const char *_mUID) : serverid(_id) {
	memset(mUID, 0, sizeof(mUID));
	Q_strncpyz(mUID, _mUID, sizeof(mUID));
	this->lastName = "Unknown Client";
}

bool mClient::Exists(mClient& mc) {
	for (auto& it : mClients) {
		if (it.serverid == mc.serverid)
			return true;
	}
	return false;
}

mClient* mClient::Find(unsigned int svid) {
	for (int i = 0; i < mClients.size(); i++) {
		if (mClients[i].serverid == svid)
			return &mClients[i];
	}
	return nullptr;
}

bool mClient::Exists(unsigned int id) {
	for (std::vector<mClient>::iterator it = mClients.begin(); it != mClients.end(); ++it) {
		if (it->serverid == id)
			return true;
	}
	return false;
}
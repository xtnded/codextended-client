#pragma once

class mClient {
public:
	unsigned int serverid;
	char mUID[33];
	std::string lastName;

	mClient(unsigned int, const char *);
	static bool Exists(mClient&);
	static bool Exists(unsigned int);

	static mClient *Find(unsigned int);
};

extern std::vector<mClient> mClients; //will print loads of errors when not defined e.g std::vector
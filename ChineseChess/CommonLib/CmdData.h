#pragma once
#include <string>

class CmdData
{
public:
	CmdData();
	~CmdData();

	std::string GetToken() { return token; }
	void SetToken(std::string iToken) { this->token = iToken; }
	std::string GetUser() { return userName; }
	void SetUserName(std::string iUserName) { userName = iUserName; }
	void SetRec(bool rec) { isOk = rec; }
	bool IsOk() { return isOk; }

protected:
	std::string token;
	std::string userName;
	bool isOk;
};


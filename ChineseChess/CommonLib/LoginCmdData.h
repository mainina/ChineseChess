#pragma once
#include "CmdData.h"
#include <string>
class LoginCmdData :
	public CmdData
{
public:
	LoginCmdData();
	~LoginCmdData();
	std::string GetPwd() { return pwd; }
	void SetPwd(std::string iPwd) { pwd = iPwd; }

private:
	std::string pwd;
};


#pragma once
#include "CmdData.h"
#include <string>
#include <vector>


class SelectCmdData :public CmdData
{
public:
	SelectCmdData();
	~SelectCmdData();

	std::string GetRoom() { return room; }
	void SetRoom(std::string iRoom) { room = iRoom; }
	std::string GetDesk() { return desk; }
	void SetDesk(std::string iDesk) { desk = iDesk; }

private:
	std::string room;
	std::string desk;
};


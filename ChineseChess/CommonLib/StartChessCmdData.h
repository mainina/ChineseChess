#pragma once
#include "CmdData.h"
class StartChessCmdData :
	public CmdData
{
public:
	StartChessCmdData();
	~StartChessCmdData();

	int GetSdPlayer() { return sdPlayer; }
	void SetSdPlayer(int iSdPlayer) { sdPlayer = iSdPlayer; }

private:
	int sdPlayer;
};


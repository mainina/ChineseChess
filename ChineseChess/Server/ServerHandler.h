#pragma once
#include "CThread.h"
#include <functional>
#include <vector>
#include "MoveCmdData.h"

using OnDisconnectEvent = std::function<void(CThread*)>;

class ServerHandler :public CThread
{
public:
	ServerHandler(SOCKET clientSocket);
	~ServerHandler();
	void Run();
	int Start();
	int Stop();
	int Forwarding(std::string cmd);
	int StartChess(std::vector<std::string> fightUser);
	int NotityMoveChess(MoveCmdData* cmdData);

private:
	SOCKET clientSocket;
	bool isBeginRecv;

public:
	OnDisconnectEvent onDisconnectEvent;
};


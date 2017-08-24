#pragma once
#include "CThread.h"
#include <functional>

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

private:
	SOCKET clientSocket;
	bool isBeginRecv;

public:
	OnDisconnectEvent onDisconnectEvent;
};


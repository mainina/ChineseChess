#pragma once
#include "CThread.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

class ClientSocket :public CThread
{
public:
	ClientSocket();
	~ClientSocket();
	int Init();
	void Run();
	int Send(std::string command);
	void Close();

private:
	SOCKET mSocket;
};


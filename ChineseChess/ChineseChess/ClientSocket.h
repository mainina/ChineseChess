#pragma once
#include "CThread.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <functional>
#include "CmdData.h"

using OnLoginCallback = std::function<void(CmdData*)>;

class ClientSocket :public CThread
{
public:
	ClientSocket();
	~ClientSocket();
	int Init();
	void Run();
	int Send(std::string command);
	void Close();
	void Login(std::string userName, std::string password, std::function<void(CmdData*)> callback);
	void SelectRoom(std::string room);
	void SelectRoomDesk(std::string room, std::string desk);
	void GoToWar();

private:
	OnLoginCallback loginCallback;
	SOCKET mSocket;
	const char chBegin = 0x02;
	const char chEnd = 0x03;

private:
	void StartChessRec();
};


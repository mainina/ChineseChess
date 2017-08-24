#pragma once
#include <stdio.h>
#include <Winsock2.h>	//Socket的函数调用　
#include <windows.h>
#include <vector>
#include "CThread.h"

#define DEFAULT_PORT "15010"

class ServerSocket
{
public:
	ServerSocket();
	~ServerSocket();
	BOOL Init();
	void Open();
	void Close();
	SOCKET GetSocket();
	BOOL IsOpen();
	void DisConnectEvent(CThread *handler);

private:
	WSADATA wsaData;
	SOCKET sServer;
	struct addrinfo *result;
	BOOL isOpen = FALSE;
};


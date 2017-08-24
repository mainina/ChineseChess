// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServerSocket.h"

int main()
{
	ServerSocket  serverSocket;
	if (serverSocket.Init())
	{
		serverSocket.Open();
	}
	return 0;
}


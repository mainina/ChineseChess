// Server.cpp : �������̨Ӧ�ó������ڵ㡣
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


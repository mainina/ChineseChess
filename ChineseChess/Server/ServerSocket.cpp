#include "stdafx.h"
#include "ServerSocket.h"
#include "ServerHandler.h"
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>



ServerSocket::ServerSocket()
{

}


ServerSocket::~ServerSocket()
{
}

BOOL ServerSocket::Init()
{
	int iResult = 0;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed： %d\n", iResult);
		return FALSE;
	}

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo is failed: %d\n", iResult);
		WSACleanup();
		return FALSE;
	}

	sServer = INVALID_SOCKET;
	sServer = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (sServer == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return FALSE;
	}

	iResult = bind(sServer, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(sServer);
		WSACleanup();
		return FALSE;
	}
	freeaddrinfo(result);

	if (listen(sServer, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(sServer);
		WSACleanup();
		return FALSE;
	}
	printf("Listen...\n");

	return TRUE;
}

DWORD WINAPI LoopAccept(LPVOID lpParam)
{
	ServerSocket* serverSocket = (ServerSocket*)lpParam;

	std::vector<ServerHandler*> threadHandle;
	printf("Open thread to accept client...\n");
	while (serverSocket->IsOpen()) {

		SOCKET clientSocket = INVALID_SOCKET;
		clientSocket = accept(serverSocket->GetSocket(), NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
		{
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(serverSocket->GetSocket());
			WSACleanup();
			break;
		}

		struct sockaddr_in addr;
		socklen_t addr_size = sizeof(struct sockaddr_in);
		int res = getpeername(clientSocket, (struct sockaddr *)&addr, &addr_size);
		char *clientip = new char[20];
		ZeroMemory(clientip, 20);
		strcpy_s(clientip, 20, inet_ntoa(addr.sin_addr));
		printf("Peer IP address: %s\n", clientip);

		ServerHandler* handler = new ServerHandler(clientSocket);
		handler->onDisconnectEvent = std::bind(&ServerSocket::DisConnectEvent, serverSocket, std::placeholders::_1);
		handler->Start();

		threadHandle.push_back(handler);
	}

	std::vector<ServerHandler*>::iterator t;
	for (t = threadHandle.begin(); t != threadHandle.end(); t++)
	{
		(*t)->Stop();
		delete (*t);
	}
	threadHandle.clear();
	serverSocket->Close();
	return 0;
}

void ServerSocket::Open()
{
	if (isOpen) {
		return;
	}
	isOpen = TRUE;
	HANDLE hThread1;
	DWORD dwThreadId1;

	// 6.创建线程执行收发数据 
	hThread1 = CreateThread(NULL, NULL, LoopAccept, (LPVOID*)this, 0, &dwThreadId1);
	WaitForSingleObject(hThread1, INFINITE);
}

void ServerSocket::Close()
{
	WSACleanup();
}

SOCKET ServerSocket::GetSocket()
{
	return sServer;
}

BOOL ServerSocket::IsOpen()
{
	return isOpen;
}

// 断开连接后的线程，判断是否已经Join
DWORD WINAPI CloseServerHandler(LPVOID lpParam)
{
	CThread* thr = (CThread*)lpParam;
	while (true)
	{
		if (thr->isExit()) {
			thr->Destory();
			break;
		}
		Sleep(200);
	}
	return 0;
}

// 断开连接事件
void ServerSocket::DisConnectEvent(CThread * handler)
{
	HANDLE hThread1;
	DWORD dwThreadId1;

	// 6.创建线程执行收发数据 
	hThread1 = CreateThread(NULL, NULL, CloseServerHandler, (LPVOID*)handler, 0, &dwThreadId1);
	WaitForSingleObject(hThread1, 1000);
	CloseHandle(hThread1);
}

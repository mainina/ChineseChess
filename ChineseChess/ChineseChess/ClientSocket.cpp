#include "stdafx.h"
#include "ClientSocket.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "Protocal.h"
#include "CommandDecoder.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "15010"
#define SERVER_IP "127.0.0.1"

ClientSocket::ClientSocket()
{
}


ClientSocket::~ClientSocket()
{
}

int ClientSocket::Init()
{
	WSADATA wsaData;
	mSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(SERVER_IP, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		mSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (mSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(mSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(mSocket);
			mSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (mSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	return 0;
}

void ClientSocket::Run()
{
	// Receive until the peer closes the connection
	int iResult = 0;
	char bufRecv[DEFAULT_BUFLEN];
	int recvBufLen = DEFAULT_BUFLEN;
	do {
		memset(bufRecv, 0, sizeof(bufRecv));
		iResult = recv(mSocket, bufRecv, recvBufLen, 0);
		if (iResult == SOCKET_ERROR) {
			printf("recive faild with error: %d\n", WSAGetLastError());
			break;
		}
		else if (iResult == 0)
		{
			printf("Connection closed\n");
			break;
		}
		else
		{
			printf("接收到服务端的消息：%s", bufRecv);
			CommandDecoder* cmdDecoder = new CommandDecoder(bufRecv);
			if (!cmdDecoder->decode())
			{
				printf("cmdDecoder error");
			}
			CmdData* data = cmdDecoder->getData();
			if (cmdDecoder->getCommand() == LRCommand)
			{
				char buff[512];
				ZeroMemory(buff, 512);
				snprintf(buff, sizeof(buff), "%c%d,%s,%s,room101%c", cmdDecoder->getChBegin(), SRCommand, data->GetUser().c_str(),data->GetToken().c_str(), cmdDecoder->getChEnd());
				std::string cmd = buff;
				Send(cmd);
			}
			else if (cmdDecoder->getCommand() == SRRCommand)
			{
				if (data->IsOk())
				{
					char buff[512];
					ZeroMemory(buff, 512);
					snprintf(buff, sizeof(buff), "%c%d,%s,%s,room101,desk01%c", cmdDecoder->getChBegin(), SDCommand, data->GetUser().c_str(), data->GetToken().c_str(), cmdDecoder->getChEnd());
					std::string cmd = buff;
					Send(cmd);
				}
			}
			delete cmdDecoder;
		}
	} while (iResult > 0);
}

int ClientSocket::Send(std::string command)
{
	// Send an initial buffer
	int iResult = send(mSocket, command.c_str(), (int)strlen(command.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return 1;
	}
	return iResult;
}

void ClientSocket::Close()
{
	int iResult = shutdown(mSocket, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return;
	}

	// cleanup
	closesocket(mSocket);
	WSACleanup();
}

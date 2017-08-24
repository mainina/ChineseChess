#include "stdafx.h"
#include "ClientSocket.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "Protocal.h"
#include "CommandDecoder.h"
#include "ChessApp.h"
#include "StartChessCmdData.h"
#include "MoveCmdData.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "15010"
#define SERVER_IP "127.0.0.1"
#define ROOM_NAME "Hight Level"
#define DESK_NAME "Desk01"

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
				loginCallback(data);
				// select room
				if (data->IsOk())
				{
					SelectRoom(ROOM_NAME);
				}
			}
			else if (cmdDecoder->getCommand() == SRRCommand)
			{
				// select desk of room
				if (data->IsOk())
				{
					SelectRoomDesk(ROOM_NAME, DESK_NAME);
				}
			}
			else if (cmdDecoder->getCommand() == SCCommand)
			{
				// apply
				StartChessRec();

				ChessApp::GetInstance()->Startup(((StartChessCmdData*)data)->GetSdPlayer());
			}
			else if (cmdDecoder->getCommand() == MCommand)
			{
				char buff[512];
				ZeroMemory(buff, 512);
				snprintf(buff, sizeof(buff), "%c%d,%s,%d%c", chBegin,
					MRCommand,
					ChessApp::GetInstance()->GetUser().GetUser().c_str(),
					true,
					chEnd);
				Send(std::string(buff));

				MoveCmdData* moveData = (MoveCmdData*)data;
				MoveStep step(abs(9 - moveData->GetSrcX()),
					abs(10 - moveData->GetSrcY()),
					abs(9 - moveData->GetDestX()),
					abs(10 - moveData->GetDestY()));
				ChessApp::GetInstance()->OtherFightMove(&step, moveData->GetSdPlayer());
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

void ClientSocket::Login(std::string userName, std::string password, std::function<void(CmdData*)> callback)
{
	if (this->loginCallback == NULL)
	{
		this->loginCallback = callback;
	}
	char buff[512];
	ZeroMemory(buff, 512);
	snprintf(buff, sizeof(buff), "%c%d,%s,%s,%c", chBegin, LCommand, userName.c_str(), password.c_str(), chEnd);
	std::string cmd = buff;
	Send(cmd);
}

void ClientSocket::SelectRoom(std::string room)
{
	char buff[512];
	ZeroMemory(buff, 512);

	snprintf(buff, sizeof(buff), "%c%d,%s,%s,%s%c", chBegin, SRCommand,
		ChessApp::GetInstance()->GetUser().GetUser().c_str(),
		ChessApp::GetInstance()->GetUser().GetToken().c_str(),
		room.c_str(),
		chEnd);
	std::string cmd = buff;
	Send(cmd);
}

void ClientSocket::SelectRoomDesk(std::string room, std::string desk)
{
	char buff[512];
	ZeroMemory(buff, 512);
	snprintf(buff, sizeof(buff), "%c%d,%s,%s,%s,%s%c", chBegin, SDCommand,
		ChessApp::GetInstance()->GetUser().GetUser().c_str(),
		ChessApp::GetInstance()->GetUser().GetToken().c_str(),
		room.c_str(),
		desk.c_str(),
		chEnd);
	std::string cmd = buff;
	Send(cmd);
}

void ClientSocket::GoToWar()
{
	char buff[512];
	ZeroMemory(buff, 512);
	snprintf(buff, sizeof(buff), "%c%d,%s,%s,%s,%s%c", chBegin, GTWCommand,
		ChessApp::GetInstance()->GetUser().GetUser().c_str(),
		ChessApp::GetInstance()->GetUser().GetToken().c_str(),
		ROOM_NAME,
		DESK_NAME,
		chEnd);

	Send(std::string(buff));
}

// Move Data-->userName,token,room,desk,sdPlayer,srcX,srcY,destX,destY
void ClientSocket::OnChessMoveEvent(MoveStep * step)
{
	char buff[512];
	ZeroMemory(buff, 512);
	snprintf(buff, sizeof(buff), "%c%d,%s,%s,%s,%s,%d,%d,%d,%d,%d%c", chBegin, MCommand,
		ChessApp::GetInstance()->GetUser().GetUser().c_str(),
		ChessApp::GetInstance()->GetUser().GetToken().c_str(),
		ROOM_NAME,
		DESK_NAME,
		ChessApp::GetInstance()->GetSdPlayer(),
		step->src.x,
		step->src.y,
		step->dest.x,
		step->dest.y,
		chEnd);

	Send(std::string(buff));
}

void ClientSocket::StartChessRec()
{
	char buff[512];
	ZeroMemory(buff, 512);
	snprintf(buff, sizeof(buff), "%c%d,%s,%d%c", chBegin,
		SCRCommand,
		ChessApp::GetInstance()->GetUser().GetUser().c_str(),
		true,
		chEnd);

	Send(std::string(buff));
}

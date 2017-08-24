#include "stdafx.h"
#include "ServerHandler.h"
#include "Decoder.h"
#include "CommandDecoder.h"
#include "CmdData.h"
#include "Protocal.h"
#include "ClientSocketStore.h"
#include "GUIDGenertor.h"

#define	BUF_SIZE 512

ServerHandler::ServerHandler(SOCKET clientSocket)
{
	this->clientSocket = clientSocket;
}

ServerHandler::~ServerHandler()
{
	closesocket(clientSocket);
}

void ServerHandler::Run()
{
	int retVal;
	char bufRecv[BUF_SIZE];
	ClientSocketStore* store = ClientSocketStore::GetInstance();
	while (isBeginRecv)
	{
		memset(bufRecv, 0, sizeof(bufRecv));
		retVal = recv(clientSocket, bufRecv, BUF_SIZE, 0);
		if (retVal == SOCKET_ERROR) {
			printf("recive faild!\n");
			isBeginRecv = false;
			onDisconnectEvent(this);
			break;
		}
		else if (retVal == 0)
		{
			printf("shutdown send Client");
			isBeginRecv = false;
			onDisconnectEvent(this);
			break;
		}
		else
		{
			printf("收到客户端消息：%s\n", bufRecv);

			CommandDecoder* cmdDecoder = new CommandDecoder(bufRecv);
			if (!cmdDecoder->decode())
			{
				printf("cmdDecoder error");
			}

			CmdData* data = cmdDecoder->getData();
			char buff[BUF_SIZE];
			ZeroMemory(buff, BUF_SIZE);
			if (cmdDecoder->getCommand() == LCommand) // Login Command
			{
				LoginCmdData user;
				user.SetUserName(data->GetUser());
				user.SetToken(newUUID());
				store->AddUser(user);
				store->AddUserSocket(user.GetUser(), clientSocket);

				snprintf(buff, sizeof(buff), "%c%d,%s,%s,%d%c", cmdDecoder->getChBegin(), LRCommand, user.GetUser().c_str(), user.GetToken().c_str(), true, cmdDecoder->getChEnd());
				Forwarding(std::string(buff));
			}
			else
			{
				if (!store->IsLogin(data->GetUser(), data->GetToken()))
				{
					// no login error
					snprintf(buff, sizeof(buff), "%c%d,%s%c", cmdDecoder->getChBegin(), AECommand, data->GetUser().c_str(), cmdDecoder->getChEnd());
					Forwarding(std::string(buff));
				}
				else
				{
					if (cmdDecoder->getCommand() == SRCommand) // Select Room Command
					{
						store->AddUserToRoom(((SelectCmdData*)data)->GetRoom(), data->GetUser());

						snprintf(buff, sizeof(buff), "%c%d,%s,%d%c", cmdDecoder->getChBegin(),
							SRRCommand,
							data->GetUser().c_str(),
							true,
							cmdDecoder->getChEnd());
						Forwarding(std::string(buff));
					}
					else if (cmdDecoder->getCommand() == SDCommand)
					{
						store->AddUserToRoomDesk(((SelectCmdData*)data)->GetRoom(),
							((SelectCmdData*)data)->GetDesk(),
							data->GetUser());

						snprintf(buff, sizeof(buff), "%c%d,%s,%d%c", cmdDecoder->getChBegin(),
							SDRCommand,
							data->GetUser().c_str(),
							true,
							cmdDecoder->getChEnd());
						Forwarding(std::string(buff));
					}
					else if (cmdDecoder->getCommand() == GTWCommand)
					{
						// todo go to war
						snprintf(buff, sizeof(buff), "%c%d,%s,%d%c", cmdDecoder->getChBegin(),
							GTWRCommand,
							data->GetUser().c_str(),
							true,
							cmdDecoder->getChEnd());
						Forwarding(std::string(buff));

						// can start
						DeskModel* deskModel = store->Player(((SelectCmdData*)data)->GetRoom(),
							((SelectCmdData*)data)->GetDesk(),
							data->GetUser());
						vector<string> fightUser;
						if (deskModel != NULL && deskModel->IsCanFight(&fightUser))
						{
							// start chess command
							StartChess(fightUser);
						}
					}
					else if (cmdDecoder->getCommand() == MCommand) // Move Comand
					{
						Forwarding(std::string("Move Command"));
					}
					else
					{
						Forwarding(std::string("No Know"));
					}
				}
			}


			delete cmdDecoder;
		}
	}

}

int ServerHandler::Start()
{
	isBeginRecv = true;
	return CThread::Start();
}

int ServerHandler::Stop()
{
	isBeginRecv = false;
	CThread::Destory();
	return 0;
}

int ServerHandler::Forwarding(std::string cmd)
{
	// Send an initial buffer

	int iResult = send(clientSocket, cmd.c_str(), (int)strlen(cmd.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	return iResult;
}

int ServerHandler::StartChess(std::vector<std::string> fightUser)
{
	char buff[BUF_SIZE];
	int sdPlay = 1;
	for (vector<string>::iterator it = fightUser.begin(); it != fightUser.end(); it++)
	{
		SOCKET fightUserSocket = ClientSocketStore::GetInstance()->GetSocketBy((*it));
		ZeroMemory(buff, BUF_SIZE);
		snprintf(buff, sizeof(buff), "%c%d,%s,%d%c", chBegin,
			SCCommand, it->c_str(), sdPlay % 2, chEnd);
		string cmd(buff);
		int iResult = send(fightUserSocket, cmd.c_str(), (int)strlen(cmd.c_str()), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			continue;
		}
		sdPlay++;
	}
	return 0;
}


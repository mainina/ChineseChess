#include "stdafx.h"
#include "ClientSocketStore.h"


ClientSocketStore::ClientSocketStore()
{
}


ClientSocketStore::~ClientSocketStore()
{
}

ClientSocketStore::ClientSocketStore(const ClientSocketStore&)
{

}

ClientSocketStore* ClientSocketStore::instance = new ClientSocketStore();
ClientSocketStore* ClientSocketStore::GetInstance()
{
	return instance;
}

void ClientSocketStore::AddUser(LoginCmdData user)
{
	bool isExist = false;
	for (std::vector<LoginCmdData>::iterator it = users.begin(); it != users.end(); it++) 
	{
		if (it->GetUser() == user.GetUser())
		{
			isExist = true;
			it->SetToken(user.GetToken());
			break;
		}
	}
	if (!isExist)
	{
		users.push_back(user);
	}
}

void ClientSocketStore::AddUserSocket(string userName, SOCKET clientSocket)
{
	if (userSocket.find(userName) == userSocket.end())
	{
		userSocket[userName] = clientSocket;
	}

}

void ClientSocketStore::AddUserToRoom(std::string room, std::string userName)
{
	bool isExist = false;
	for (vector<RoomModel>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		if (it->GetRoom() == room)
		{
			isExist = true;
			it->AddUser(userName);
			break;
		}
	}
	if (!isExist)
	{
		RoomModel model(room);
		model.AddUser(userName);
		rooms.push_back(model);
	}
}

void ClientSocketStore::AddUserToRoomDesk(std::string room, string desk, std::string userName)
{
	for (vector<RoomModel>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		if (it->GetRoom() == room)
		{
			it->AddDeskIfNoExit(desk, userName);
			break;
		}
	}
}

bool ClientSocketStore::IsLogin(string userName, string token)
{
	for each(LoginCmdData u in users)
	{
		if (u.GetUser() == userName && u.GetToken() == token)
		{
			return true;
		}
	}
	return false;
}

DeskModel* ClientSocketStore::Player(string room, string desk, string userName)
{
	for (vector<RoomModel>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		if (it->GetRoom() == room)
		{
			DeskModel* deskM = it->FindDeskBy(desk);
			if (deskM != NULL)
			{
				deskM->GoToWar(userName);
				return deskM;
			}
		}
	}
	return NULL;
}

SOCKET ClientSocketStore::GetSocketBy(string userName)
{
	return userSocket[userName];
}

SOCKET ClientSocketStore::FindOtherFighter(string room, string desk, string userName)
{
	for (vector<RoomModel>::iterator it = rooms.begin(); it != rooms.end(); it++)
	{
		if (it->GetRoom() == room)
		{
			DeskModel* deskM = it->FindDeskBy(desk);
			if (deskM != NULL)
			{
				return userSocket[deskM->FindOtherFight(userName)];
			}
		}
	}
	return NULL;
}

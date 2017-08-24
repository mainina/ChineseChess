#pragma once
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <Winsock2.h>	//Socket的函数调用　
#include <windows.h>
#include <vector>
#include <unordered_map>
#include "LoginCmdData.h"
#include "SelectCmdData.h"
#include "GameModel.h"

using namespace std;

class ClientSocketStore
{
public:
	static ClientSocketStore* GetInstance();
	void AddUser(LoginCmdData user);
	void AddUserSocket(string userName, SOCKET clientSocket);
	void AddUserToRoom(std::string room, std::string userName);
	void AddUserToRoomDesk(std::string room, string desk, std::string userName);
	bool IsLogin(string userName, string token);

private:
	ClientSocketStore();
	~ClientSocketStore();
	ClientSocketStore(const ClientSocketStore&);
	ClientSocketStore& operator=(const ClientSocketStore&);

	static ClientSocketStore* instance;
	vector<LoginCmdData> users;
	std::unordered_map<string, SOCKET> userSocket;
	vector<RoomModel> rooms;
};
#endif

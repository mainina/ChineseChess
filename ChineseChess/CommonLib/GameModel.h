#pragma once
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;
class DeskModel
{
public:
	DeskModel(string iDesk)
	{
		desk = iDesk;
	}
	string GetDesk() { return desk; }
	void addUser(string userName)
	{
		bool isExist = false;
		for each(string u in users)
		{
			if (u == userName)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			users.push_back(userName);
		}
	}
private:
	string desk;
	vector<string> users;
};

class RoomModel
{
public:
	RoomModel(string iRoom) { room = iRoom; }
	~RoomModel() {}
	string GetRoom() { return room; }
	void AddUser(string userName)
	{
		bool isExist = false;
		for each(string u in users)
		{
			if (u == userName)
			{
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			users.push_back(userName);
		}
	}

	void AddDeskIfNoExit(string desk, string user)
	{
		bool isExist = false;
		for (vector<DeskModel>::iterator it = desks.begin(); it != desks.end(); it++)
		{
			if (it->GetDesk() == desk)
			{
				it->addUser(user);
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			DeskModel model(desk);
			model.addUser(user);
			desks.push_back(model);
		}
		users.erase(std::remove(users.begin(), users.end(), user), users.end());
	}

private:
	string room;
	vector<DeskModel> desks;
	vector<string> users;
};


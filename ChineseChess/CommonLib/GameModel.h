#pragma once
#include <string>
#include <vector>
#include <algorithm> 
#include <unordered_map>

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
			placards[userName] = false;
		}
	}

	void GoToWar(string userName)
	{
		for each(string u in users)
		{
			if (u == userName)
			{
				placards[userName] = true;
				break;
			}
		}
	}

	bool IsCanFight(vector<string>* fightUser)
	{
		int index = 0;
		for (unordered_map<string, bool>::iterator it = placards.begin(); it != placards.end(); it++)
		{
			if (it->second)
			{
				index++;
				fightUser->push_back(it->first);
			}
		}
		if (index == 2)
		{
			return true;
		}
		return false;
	}

	bool ContainUser(string userName)
	{
		for (vector<string>::iterator it = users.begin(); it != users.end(); it++)
		{
			if ((*it) == userName)
			{
				return true;
			}
		}
		return false;
	}

private:
	string desk;
	vector<string> users;
	unordered_map<string, bool> placards;
};

class RoomModel
{
public:
	RoomModel(string iRoom) { room = iRoom; }
	~RoomModel()
	{
		for (vector<DeskModel*>::iterator it = desks.begin(); it != desks.end(); it++)
		{
			delete (*it);
		}
		desks.empty();
	}
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
		for (vector<DeskModel*>::iterator it = desks.begin(); it != desks.end(); it++)
		{
			if ((*it)->GetDesk() == desk)
			{
				(*it)->addUser(user);
				isExist = true;
				break;
			}
		}
		if (!isExist)
		{
			DeskModel* model = new DeskModel(desk);
			model->addUser(user);
			desks.push_back(model);
		}
		users.erase(std::remove(users.begin(), users.end(), user), users.end());
	}

	DeskModel* FindDeskBy(string desk)
	{
		for (vector<DeskModel*>::iterator it = desks.begin(); it != desks.end(); it++)
		{
			if ((*it)->GetDesk() == desk)
			{
				return (*it);
			}
		}
		return NULL;
	}

private:
	string room;
	vector<DeskModel*> desks;
	vector<string> users;
};


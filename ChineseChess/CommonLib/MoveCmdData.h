#pragma once
#include "CmdData.h"
#include <string>

class MoveCmdData :
	public CmdData
{
public:
	MoveCmdData();
	~MoveCmdData();

	std::string GetRoom() { return room; }
	void SetRoom(std::string iRoom) { room = iRoom; }
	std::string GetDesk() { return desk; }
	void SetDesk(std::string iDesk) { desk = iDesk; }
	void SetSrcX(int ix) { srcX = ix; }
	void SetSrcY(int iy) { srcY = iy; }
	void SetDestX(int ix) { destX = ix; }
	void SetDestY(int iy) { destY = iy; }
	void SetSdPlayer(int iSdPlayer) { sdPlayer = iSdPlayer; }
	int GetSrcX() { return srcX; }
	int GetSrcY() { return srcY; }
	int GetDestX() { return destX; }
	int GetDestY() { return destY; }
	int GetSdPlayer() { return sdPlayer; }

private:
	// Move Data-->userName,token,room,desk,sdPlayer,srcX,srcY,destX,destY
	std::string room;
	std::string desk;
	int sdPlayer;
	int srcX, srcY, destX, destY;
};


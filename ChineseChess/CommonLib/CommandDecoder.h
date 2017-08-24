#pragma once
#include <string>
#include "Decoder.h"
#include "CmdData.h"
#include <vector>

class CommandDecoder: public Decoder
{
public:
	CommandDecoder(char bufRecv[]);
	~CommandDecoder();

	virtual bool decode();
	CmdData* getData() { return mCmdData; }

	int getCommand() { return cmd; }
	const char getChBegin() { return chBegin; }
	const char getChEnd() { return chEnd; }
	
protected:
	const char chBegin = 0x02;
	const char chEnd = 0x03;
	int cmd;
	CmdData* mCmdData;
};


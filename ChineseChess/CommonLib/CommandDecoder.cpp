#include "stdafx.h"
#include "CommandDecoder.h"
#include <vector>
#include "Protocal.h"
#include "SelectCmdData.h"
#include "LoginCmdData.h"
#include "StartChessCmdData.h"
#include "MoveCmdData.h"


CommandDecoder::CommandDecoder(char bufRecv[]) :Decoder(bufRecv)
{
	mCmdData = NULL;
}

CommandDecoder::~CommandDecoder()
{
	if (mCmdData != NULL)
	{
		delete mCmdData;
	}
}

std::string removeLastCharIfHasEnd(char* txt)
{
	std::string temp = txt;
	if (temp.rfind(0x03) != -1)
	{
		temp.pop_back();
	}
	return temp;
}

bool CommandDecoder::decode()
{
	if (mBufRecv[0] != chBegin) {
		return false;
	}

	std::vector<std::string> mData;
	char* next = NULL;
	char* splitStr = strtok_s(mBufRecv + 1, ",", &next);
	if (splitStr != NULL)
	{
		cmd = atoi(splitStr);
	}
	while (splitStr != NULL)
	{
		mData.push_back(removeLastCharIfHasEnd(splitStr));
		splitStr = strtok_s(NULL, ",", &next);
	}
	switch (cmd)
	{
	case LCommand:
		mCmdData = new LoginCmdData();
		mCmdData->SetUserName(mData.at(1));
		((LoginCmdData*)mCmdData)->SetPwd(mData.at(2));
		if (mData.size() > 3 && mData.at(3)[0] != chEnd)
		{
			mCmdData->SetToken(mData.at(3));
		}
		break;
	case SRCommand:
		mCmdData = new SelectCmdData();
		mCmdData->SetUserName(mData.at(1));
		mCmdData->SetToken(mData.at(2));
		((SelectCmdData*)mCmdData)->SetRoom(mData.at(3));
		break;

	case SDCommand:
		mCmdData = new SelectCmdData();
		mCmdData->SetUserName(mData.at(1));
		mCmdData->SetToken(mData.at(2));
		((SelectCmdData*)mCmdData)->SetRoom(mData.at(3));
		((SelectCmdData*)mCmdData)->SetDesk(mData.at(4));
		break;
	case GTWCommand:
		mCmdData = new SelectCmdData();
		mCmdData->SetUserName(mData.at(1));
		mCmdData->SetToken(mData.at(2));
		((SelectCmdData*)mCmdData)->SetRoom(mData.at(3));
		((SelectCmdData*)mCmdData)->SetDesk(mData.at(4));
		break;
	case LRCommand:
		mCmdData = new CmdData();
		mCmdData->SetUserName(mData.at(1));
		mCmdData->SetToken(mData.at(2));
		if (mData.size() > 3 && mData.at(3)[0] == '1')
		{
			mCmdData->SetRec(true);
		}
		else
		{
			mCmdData->SetRec(false);
		}
		break;
	case SCCommand:
		mCmdData = new StartChessCmdData();
		mCmdData->SetUserName(mData.at(1));
		((StartChessCmdData*)mCmdData)->SetSdPlayer(atoi(mData.at(2).c_str()));
		break;
	case MCommand:
		mCmdData = new MoveCmdData();
		mCmdData->SetUserName(mData.at(1));
		mCmdData->SetToken(mData.at(2));
		((MoveCmdData*)mCmdData)->SetRoom(mData.at(3));
		((MoveCmdData*)mCmdData)->SetDesk(mData.at(4));
		((MoveCmdData*)mCmdData)->SetSdPlayer(atoi(mData.at(5).c_str()));
		((MoveCmdData*)mCmdData)->SetSrcX(atoi(mData.at(6).c_str()));
		((MoveCmdData*)mCmdData)->SetSrcY(atoi(mData.at(7).c_str()));
		((MoveCmdData*)mCmdData)->SetDestX(atoi(mData.at(8).c_str()));
		((MoveCmdData*)mCmdData)->SetDestY(atoi(mData.at(9).c_str()));
		break;
	case MRCommand:
	case SCRCommand:
	case SRRCommand:
	case SDRCommand:
	case GTWRCommand:
		mCmdData = new CmdData();
		mCmdData->SetUserName(mData.at(1));
		if (mData.size() > 2 && mData.at(2)[0] == '1')
		{
			mCmdData->SetRec(true);
		}
		else
		{
			mCmdData->SetRec(false);
		}
		break;
	default:
		break;
	}

	return true;
}

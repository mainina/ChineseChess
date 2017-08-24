#include "stdafx.h"
#include "CommandDecoder.h"
#include <vector>
#include "Protocal.h"
#include "SelectCmdData.h"
#include "LoginCmdData.h"


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
	case LRCommand:
	case SRRCommand:
	case SDRCommand:
		mCmdData = new CmdData();
		mCmdData->SetUserName(mData.at(1));
		mCmdData->SetToken(mData.at(2));
		if (mData.at(3)[0] == '1')
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

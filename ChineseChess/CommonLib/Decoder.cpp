#include "stdafx.h"
#include "Decoder.h"
#include <WS2tcpip.h>
#include <stdio.h>


Decoder::Decoder(char bufRecv[])
{
	ZeroMemory(this->mBufRecv, 512);
	strcpy_s(mBufRecv, bufRecv);
}

Decoder::~Decoder()
{
}

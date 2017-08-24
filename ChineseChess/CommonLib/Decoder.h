#pragma once
class Decoder
{
public:
	Decoder(char bufRecv[]);
	~Decoder();
	virtual bool decode() = 0;

protected:
	char mBufRecv[512];
};


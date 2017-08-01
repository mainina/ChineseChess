#pragma once
#include "Config.h"

class ChessApp
{
public:
	HINSTANCE hInst;
	HWND hWnd;

public:
	ChessApp();
	~ChessApp();
	void Startup(void);
};


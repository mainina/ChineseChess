#pragma once
#include "Config.h"
#include "ChessBoard.h"

class ChessApp
{
private:
	ChessBoard* cBoard;

public:
	HINSTANCE hInst;
	HWND hWnd;

public:
	ChessApp();
	~ChessApp();
	void Startup(void);
	void DrawBoard(HDC hdc);
};


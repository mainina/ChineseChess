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
	HDC hdc, hdcTmp;
	POINT sqSelected;
	HBITMAP bmpSelected;
	MoveStep*	mvLast;
	BOOL bFlipped;

public:
	ChessApp();
	~ChessApp();
	void Startup(void);
	void DrawBoard(HDC hdc);
	void DrawSquare(POINT pieceLocation, BOOL bSelected);
	void NotSelect(void);
	void Click(int x, int y);
	BOOL IsSelected(void);
};


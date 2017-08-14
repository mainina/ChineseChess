#pragma once
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
	ChessApp(void);
	~ChessApp(void);
	void Startup(void);
	void DrawBoard(HDC hdc);
	void DrawSquare(POINT pieceLocation, BOOL bSelected);
	void NotSelect(void);
	void Click(int x, int y);
	BOOL IsSelected(void);

private:
	void ShowDialog(void);
};


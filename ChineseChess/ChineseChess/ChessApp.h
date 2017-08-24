#pragma once
#include "ChessBoard.h"
#include "LoginCmdData.h"

class ChessApp
{
private:
	ChessBoard* cBoard;
	ChessApp(void);
	~ChessApp(void);
	static ChessApp* instance;
	LoginCmdData user;


public:
	HINSTANCE hInst;
	HWND hWnd;
	HDC hdc, hdcTmp;
	POINT sqSelected;
	HBITMAP bmpSelected;
	MoveStep*	mvLast;
	BOOL bFlipped;

public:
	static ChessApp* GetInstance();
	void Startup(void);
	void DrawBoard(HDC hdc);
	void DrawSquare(POINT pieceLocation, BOOL bSelected);
	void NotSelect(void);
	void Click(int x, int y);
	BOOL IsSelected(void);
	void SetUser(LoginCmdData* user);
	LoginCmdData GetUser() { return user; }

private:
	void ShowDialog(void);
};


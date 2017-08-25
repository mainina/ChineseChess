#pragma once
#include "ChessBoard.h"
#include "LoginCmdData.h"
#include <functional>

using OnChessMoveEvent = std::function<void(MoveStep*)>;

class ChessApp
{
private:
	ChessBoard* cBoard;
	ChessApp(void);
	~ChessApp(void);
	static ChessApp* instance;
	LoginCmdData user;
	int sdPlayer;
	OnChessMoveEvent onChessMoveEvent;
	bool isWaiting;

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
	void Startup(int);
	void DrawBoard(HDC hdc);
	void DrawSquare(POINT pieceLocation, BOOL bSelected);
	void NotSelect(void);
	void Click(int x, int y);
	BOOL IsSelected(void);
	void SetUser(LoginCmdData* user);
	LoginCmdData GetUser() { return user; }
	int GetSdPlayer();
	void AddChessMoveEvent(std::function<void(MoveStep*)>);
	void OtherFightMove(MoveStep* step, int changeSide);
	bool IsWaiting() { return isWaiting; }
	void SetWaiting(bool val) { isWaiting = val; }

private:
	void ShowDialog(void);
	void ShowWinDialog(int sdPlayer);
	void ClickOrMove(int x, int y);
};


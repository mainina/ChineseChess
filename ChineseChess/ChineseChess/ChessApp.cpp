#include "stdafx.h"
#include "ChessApp.h"
#include "Util.h"
#include "resource.h"


ChessApp::ChessApp()
{
	cBoard = new ChessBoard();
}


ChessApp::~ChessApp()
{
	if (cBoard != NULL)
	{
		delete cBoard;
	}
}

void ChessApp::Startup(void)
{
	cBoard->Startup(hInst);
}

void ChessApp::DrawBoard(HDC hdc)
{
	cBoard->DrawBoard(hdc);
}

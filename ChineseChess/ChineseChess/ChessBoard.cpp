#include "stdafx.h"
#include "ChessBoard.h"
#include "Config.h"
#include "Util.h"
#include "resource.h"

ChessBoard::ChessBoard()
{
}


ChessBoard::~ChessBoard()
{
}

void ChessBoard::Startup(HINSTANCE hInstance)
{
	bmpBoard = LoadResBmp(hInstance, IDB_BOARD);
}

HDC ChessBoard::DrawBoard(HDC hdc)
{
	int xx, yy;
	HDC hdcTmp;

	// ª≠∆Â≈Ã
	hdcTmp = CreateCompatibleDC(hdc);
	SelectObject(hdcTmp, bmpBoard);
	BitBlt(hdc, 0, 0, BOARD_WIDTH, BOARD_HEIGHT, hdcTmp, 0, 0, SRCCOPY);

	return hdcTmp;
}

HBITMAP ChessBoard::Bmp(void)
{
	return bmpBoard;
}

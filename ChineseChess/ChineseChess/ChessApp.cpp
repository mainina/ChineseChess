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
	HDC hdcTmp = cBoard->DrawBoard(hdc);
	if (IsSelected())
	{
		int xx = BOARD_EDGE + sqSelected.x * SQUARE_SIZE;
		int yy = BOARD_EDGE + sqSelected.y * SQUARE_SIZE;
		DrawTransBmp(hdc, hdcTmp, xx, yy, bmpSelected);
	}
	DeleteDC(hdcTmp);
}

// »æÖÆ¸ñ×Ó
void ChessApp::DrawSquare(POINT pieceLocation, BOOL bSelected = FALSE) {
	int xx, yy;

	xx = BOARD_EDGE + pieceLocation.x * SQUARE_SIZE;
	yy = BOARD_EDGE + pieceLocation.y * SQUARE_SIZE;
	SelectObject(hdcTmp, cBoard->Bmp());
	BitBlt(hdc, xx, yy, SQUARE_SIZE, SQUARE_SIZE, hdcTmp, xx, yy, SRCCOPY);

	ChessPiece* piece = cBoard->FindPiece(pieceLocation.x, pieceLocation.y);
	if (piece != NULL) {
		DrawTransBmp(hdc, hdcTmp, xx, yy, piece->Bmp());
	}
	if (bSelected) {
		DrawTransBmp(hdc, hdcTmp, xx, yy, bmpSelected);
	}
}

void ChessApp::NotSelect(void)
{
	sqSelected.x = -1;
	sqSelected.y = -1;
}

void ChessApp::Click(int x, int y)
{
	/***

	***/
}

BOOL ChessApp::IsSelected(void)
{
	return sqSelected.x >= 0 && sqSelected.y >= 0;
}

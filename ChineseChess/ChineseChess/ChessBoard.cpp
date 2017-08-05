#include "stdafx.h"
#include "ChessBoard.h"
#include "Config.h"
#include "Util.h"
#include "resource.h"
#include "KingPiece.h"

typedef std::vector<ChessPiece*> Vint;

ChessBoard::ChessBoard()
{
}


ChessBoard::~ChessBoard()
{
	if (!pieceVector.empty())
	{
		for (Vint::iterator it = pieceVector.begin(); it != pieceVector.end(); it++)
		{
			delete (*it);
		}
	}
}

void ChessBoard::Startup(HINSTANCE hInstance)
{
	bmpBoard = LoadResBmp(hInstance, IDB_BOARD);
	ChessPiece* backKing = new KingPiece(this, hInstance, BACK);
	ChessPiece* redKing = new KingPiece(this, hInstance, RED);
	pieceVector.push_back(backKing);
	pieceVector.push_back(redKing);
}

HDC ChessBoard::DrawBoard(HDC hdc)
{
	int xx, yy;
	HDC hdcTmp;

	// »­ÆåÅÌ
	hdcTmp = CreateCompatibleDC(hdc);
	SelectObject(hdcTmp, bmpBoard);
	BitBlt(hdc, 0, 0, BOARD_WIDTH, BOARD_HEIGHT, hdcTmp, 0, 0, SRCCOPY);

	// »­Æå×Ó
	for (Vint::iterator it = pieceVector.begin(); it != pieceVector.end(); it++)
	{
		xx = BOARD_EDGE + (*it)->Location().x * SQUARE_SIZE;
		yy = BOARD_EDGE + (*it)->Location().y * SQUARE_SIZE;
		DrawTransBmp(hdc, hdcTmp, xx, yy, (*it)->Bmp());
	}

	return hdcTmp;
}

HBITMAP ChessBoard::Bmp(void)
{
	return bmpBoard;
}

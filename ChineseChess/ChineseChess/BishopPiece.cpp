#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "BishopPiece.h"
#include "ChessBoard.h"

BishopPiece::BishopPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_BISHOP;
}

BishopPiece::BishopPiece(ChessBoard* board, HINSTANCE hInst, int color)
	:ChessPiece(board, hInst, color)
{
	new (this)BishopPiece(board);
	if(color == BACK)
	{
		name = "œÛ";
		bmpPiece = LoadResBmp(hInst, IDB_BB);


		location.x = 2;
		location.y = 0;
	}
	else
	{
		name = "œ‡";
		bmpPiece = LoadResBmp(hInst, IDB_RB);

		location.x = 2;
		location.y = 9;
	}
}


BishopPiece::~BishopPiece(void)
{
}

BOOL BishopPiece::Check(MoveStep* step)
{
	return TRUE;
}

int BishopPiece::Count(void)
{
	return 2;
}
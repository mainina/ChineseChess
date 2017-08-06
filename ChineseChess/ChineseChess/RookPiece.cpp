#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "RookPiece.h"
#include "ChessBoard.h"


RookPiece::RookPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_ROOK;
}

RookPiece::RookPiece(ChessBoard* board, HINSTANCE hInst, int color)
	:ChessPiece(board, hInst, color)
{
	new (this)RookPiece(board);

	if(color == BACK)
	{
		name = "܇";
		bmpPiece = LoadResBmp(hInst, IDB_BR);

		location.x = 0;
		location.y = 0;
	}
	else
	{
		name = "܇";
		bmpPiece = LoadResBmp(hInst, IDB_RR);

		location.x = 0;
		location.y = 9;
	}
}


RookPiece::~RookPiece(void)
{
}

BOOL RookPiece::Check(MoveStep* step)
{
	return TRUE;
}

int RookPiece::Count(void)
{
	return 2;
}
#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "KnightPiece.h"
#include "ChessBoard.h"

KnightPiece::KnightPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_KNIGHT;
}

KnightPiece::KnightPiece(ChessBoard* board, HINSTANCE hInst, int color)
	:ChessPiece(board, hInst,color)
{
	new (this)KnightPiece(board);

	if(color == BACK)
	{
		name = "ÒR";
		bmpPiece = LoadResBmp(hInst, IDB_BN);


		location.x = 1;
		location.y = 0;
	}
	else
	{
		name = "ÒR";
		bmpPiece = LoadResBmp(hInst, IDB_RN);

		location.x = 1;
		location.y = 9;
	}
}


KnightPiece::~KnightPiece(void)
{
}

BOOL KnightPiece::Check(MoveStep* step)
{
	return TRUE;
}

int KnightPiece::Count(void)
{
	return 2;
}

#include "stdafx.h"
#include "Util.h"
#include "resource.h"
#include "KingPiece.h"


KingPiece::KingPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_KING;
}

KingPiece::KingPiece(ChessBoard* board, HINSTANCE hInst, int color)
	:ChessPiece(board,hInst, color)
{
	new (this)KingPiece(board);

	if(color == BACK)
	{
		name = "½«";
		bmpPiece = LoadResBmp(hInst, IDB_BK);


		location.x = 4;
		location.y = 0;
	}
	else
	{
		name = "Ë§";
		bmpPiece = LoadResBmp(hInst, IDB_RK);

		location.x = 4;
		location.y = 9;
	}
}


KingPiece::~KingPiece(void)
{
}

BOOL KingPiece::Check(MoveStep* step)
{
	return TRUE;
}

int KingPiece::Count(void)
{
	return 1;
}

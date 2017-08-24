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
		name = "ñR";
		bmpPiece = LoadResBmp(hInst, IDB_BN);
	}
	else
	{
		name = "ñR";
		bmpPiece = LoadResBmp(hInst, IDB_RN);
	}
	if (board->SdPlayer() == color)
	{
		location.x = 1;
		location.y = 9;
	}
	else
	{
		location.x = 1;
		location.y = 0;
	}
}


KnightPiece::~KnightPiece(void)
{
}

BOOL KnightPiece::Check(MoveStep* step)
{
	BOOL condition1 = step->dest.x >= 0 && step->dest.x <= 8;
	BOOL condition2 = step->dest.y >= 0 && step->dest.y <= 9;

	int xd = abs(step->dest.x - step->src.x);
	int yd = abs(step->dest.y - step->src.y);
	BOOL condition3 = (xd == 1 && yd == 2) || (xd == 2 && yd == 1);

	int ym = -1, xm = -1;
	if(xd == 2)
	{
		ym = step->src.y;
		xm = step->dest.x > step->src.x ? step->dest.x - 1 : step->dest.x + 1;
	}
	else
	{
		xm = step->src.x;
		ym = step->dest.y > step->src.y ? step->dest.y - 1 : step->dest.y + 1;
	}
	BOOL condition4 = board->FindPiece(xm, ym) == NULL;

	return condition1 && condition2 && condition3 && condition4;
}

int KnightPiece::Count(void)
{
	return 2;
}

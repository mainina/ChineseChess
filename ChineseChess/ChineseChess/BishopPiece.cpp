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
		name = "Ïó";
		bmpPiece = LoadResBmp(hInst, IDB_BB);


		location.x = 2;
		location.y = 0;
	}
	else
	{
		name = "Ïà";
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
	BOOL condition1 = step->dest.x >= 0 && step->dest.x <= 8;
	BOOL condition2 = FALSE, condition3 = FALSE;
	if(color == BACK)
	{
		condition2 = step->dest.y >= 0 && step->dest.y <= 4;
	}
	else
	{
		condition2 = step->dest.y >= 5 && step->dest.y <= 9;
	}
	int xd = abs(step->dest.x - step->src.x);
	int yd = abs(step->dest.y - step->src.y);
	condition3 = xd == yd && xd == 2;

	int mx = step->dest.x > step->src.x ? step->dest.x - 1 : step->dest.x + 1;
	int my = step->dest.y > step->src.y ? step->dest.y - 1 : step->dest.y + 1;

	BOOL condition4 = board->FindPiece(mx, my) == NULL;

	return condition1 && condition2 && condition3 && condition4;
}

int BishopPiece::Count(void)
{
	return 2;
}
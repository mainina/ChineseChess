#include "stdafx.h"
#include "Util.h"
#include "resource.h"
#include "AdvisorPiece.h"


AdvisorPiece::AdvisorPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_ADVISOR;
}

AdvisorPiece::AdvisorPiece(ChessBoard* board, HINSTANCE hInst, int color)
	:ChessPiece(board, hInst, color)
{
	new (this)AdvisorPiece(board);
	if(color == BACK)
	{
		name = "Ê¿";
		bmpPiece = LoadResBmp(hInst, IDB_BA);

		location.x = 3;
		location.y = 0;
	}
	else
	{
		name = "ÊË";
		bmpPiece = LoadResBmp(hInst, IDB_RA);

		location.x = 3;
		location.y = 9;
	}
}

AdvisorPiece::~AdvisorPiece(void)
{
}

BOOL AdvisorPiece::Check(MoveStep* step)
{
	BOOL condition1 = step->dest.x >= 3 && step->dest.x <= 5;
	BOOL condition2 = FALSE, condition3 = FALSE;
	if(color == BACK)
	{
		condition2 = step->dest.y >= 0 && step->dest.y <= 2;
	}
	else
	{
		condition2 = step->dest.y >= 7 && step->dest.y <= 9;
	}
	int xd = abs(step->dest.x - step->src.x);
	int yd = abs(step->dest.y - step->src.y);
	condition3 = xd == yd && xd == 1;
	return condition1 && condition2 && condition3;
}

int AdvisorPiece::Count(void)
{
	return 2;
}
#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "PawnPiece.h"
#include "ChessBoard.h"
#include "ChessApp.h"


PawnPiece::PawnPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_PAWN;
}

PawnPiece::PawnPiece(ChessBoard* board, HINSTANCE hInst, int color)
	:ChessPiece(board, hInst, color)
{
	new (this)PawnPiece(board);
	if(color == BACK)
	{
		name = "×ä";
		bmpPiece = LoadResBmp(hInst, IDB_BP);
	}
	else
	{
		name = "±ø";
		bmpPiece = LoadResBmp(hInst, IDB_RP);
	}

	if (board->SdPlayer() == color)
	{
		location.x = 0;
		location.y = 6;
	}
	else
	{
		location.x = 0;
		location.y = 3;
	}
}


PawnPiece::~PawnPiece(void)
{
}

BOOL PawnPiece::Check(MoveStep* step)
{
	BOOL condition1 = FALSE;
	BOOL condition2 = TRUE;
	if(color != ChessApp::GetInstance()->GetSdPlayer())
	{
		condition1 = step->dest.y >= 3 && step->dest.y <= 5 && step->src.x == step->dest.x && (step->dest.y - step->src.y) == 1;
		if(step->dest.y >=5)
		{
			int xd = abs(step->dest.x - step->src.x);
			int yd = step->dest.y - step->src.y;
			if(xd > 1 || abs(yd) > 1 || yd < 0)
			{
				condition2 = FALSE;
			}
			else
			{
				condition2 = (xd == 1 && abs(yd) == 0) || (abs(yd) == 1 && xd == 0);
			}
		}
		else
		{
			condition2 = FALSE;
		}
	}
	else
	{
		condition1 = step->dest.y >= 4 && step->dest.y <= 6 && step->src.x == step->dest.x && (step->dest.y - step->src.y) == -1;
		if(step->dest.y <= 4)
		{
			int xd = abs(step->dest.x - step->src.x);
			int yd = step->dest.y - step->src.y;
			if(xd > 1 || abs(yd) > 1 || yd > 0)
			{
				condition2 = FALSE;
			}
			else
			{
				condition2 = (xd == 1 && abs(yd) == 0) || (abs(yd) == 1 && xd == 0);
			}
		}
		else
		{
			condition2 = FALSE;
		}
	}
	if(!condition1)
	{
		return condition2;
	}

	return condition1;
}

int PawnPiece::Count(void)
{
	return 5;
}

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
	BOOL condition1 = step->dest.x >= 0 && step->dest.x <= 8;
	BOOL condition2 = step->dest.y >= 0 && step->dest.y <= 9;

	int xd = abs(step->dest.x - step->src.x);
	int yd = abs(step->dest.y - step->src.y);
	BOOL condition3 = (xd == 0 && yd > 0) || (xd > 0 && yd == 0);
	BOOL condition4 = TRUE;

	if(xd == 0)
	{
		if(step->dest.y > step->src.y)
		{
			for(LONG y0 = step->src.y + 1; y0 < step->dest.y; y0++)
			{
				if(board->FindPiece(step->dest.x, y0) != NULL)
				{
					condition4 = FALSE;
					break;
				}
			}
		}
		else
		{
			for(LONG y0 = step->dest.y + 1; y0 < step->src.y; y0++)
			{
				if(board->FindPiece(step->dest.x, y0) != NULL)
				{
					condition4 = FALSE;
					break;
				}
			}
		}
	}
	else
	{
		if(step->dest.x > step->src.x)
		{
			for(LONG x0 = step->src.x + 1; x0 < step->dest.x; x0++)
			{
				if(board->FindPiece(x0, step->dest.y) != NULL)
				{
					condition4 = FALSE;
					break;
				}
			}
		}
		else
		{
			for(LONG x0 = step->dest.x + 1; x0 < step->src.x; x0++)
			{
				if(board->FindPiece(x0, step->dest.y) != NULL)
				{
					condition4 = FALSE;
					break;
				}
			}
		}
	}

	return condition1 && condition2 && condition3 && condition4;
}

int RookPiece::Count(void)
{
	return 2;
}
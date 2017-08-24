#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "CannonPiece.h"
#include "ChessBoard.h"


CannonPiece::CannonPiece(ChessBoard* board)
	:ChessPiece(board)
{
	id = PIECE_CANNON;
}

CannonPiece::CannonPiece(ChessBoard* board, HINSTANCE hInst, int color)
	: ChessPiece(board, hInst, color)
{
	new (this)CannonPiece(board);

	if (color == BACK)
	{
		name = "ез";
		bmpPiece = LoadResBmp(hInst, IDB_BC);
	}
	else
	{
		name = "ез";
		bmpPiece = LoadResBmp(hInst, IDB_RC);
	}
	if (board->SdPlayer() == color)
	{
		location.x = 1;
		location.y = 7;
	}
	else
	{
		location.x = 1;
		location.y = 2;
	}
}


CannonPiece::~CannonPiece(void)
{
}

BOOL CannonPiece::Check(MoveStep* step)
{
	BOOL condition1 = step->dest.x >= 0 && step->dest.x <= 8;
	BOOL condition2 = step->dest.y >= 0 && step->dest.y <= 9;

	int xd = abs(step->dest.x - step->src.x);
	int yd = abs(step->dest.y - step->src.y);
	BOOL condition3 = (xd == 0 && yd > 0) || (xd > 0 && yd == 0);

	BOOL condition4 = TRUE;
	int middleCount = 0;
	if (xd == 0)
	{
		if (step->dest.y > step->src.y)
		{
			for (LONG y0 = step->src.y + 1; y0 < step->dest.y; y0++)
			{
				if (board->FindPiece(step->dest.x, y0) != NULL)
				{
					middleCount++;
					if (middleCount > 1)
					{
						condition4 = FALSE;
						break;
					}
				}
			}
		}
		else
		{
			for (LONG y0 = step->dest.y + 1; y0 < step->src.y; y0++)
			{
				if (board->FindPiece(step->dest.x, y0) != NULL)
				{
					middleCount++;
					if (middleCount > 1)
					{
						condition4 = FALSE;
						break;
					}
				}
			}
		}
	}
	else
	{
		if (step->dest.x > step->src.x)
		{
			for (LONG x0 = step->src.x + 1; x0 < step->dest.x; x0++)
			{
				if (board->FindPiece(x0, step->dest.y) != NULL)
				{
					middleCount++;
					if (middleCount > 1)
					{
						condition4 = FALSE;
						break;
					}
				}
			}
		}
		else
		{
			for (LONG x0 = step->dest.x + 1; x0 < step->src.x; x0++)
			{
				if (board->FindPiece(x0, step->dest.y) != NULL)
				{
					middleCount++;
					if (middleCount > 1)
					{
						condition4 = FALSE;
						break;
					}
				}
			}
		}
	}

	if (condition4)
	{
		ChessPiece* piece = board->FindPiece(step->dest.x, step->dest.y);
		if (middleCount == 1)
		{
			condition4 = piece != NULL && piece->Color() != board->SdPlayer();
		}
		else
		{
			condition4 = piece == NULL;
		}
	}


	return condition1 && condition2 && condition3 && condition4;
}

int CannonPiece::Count(void)
{
	return 2;
}

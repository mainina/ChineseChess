#include "stdafx.h"
#include "Util.h"
#include "resource.h"
#include "KingPiece.h"
#include "ChessBoard.h"
#include "ChessApp.h"


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
	}
	else
	{
		name = "Ë§";
		bmpPiece = LoadResBmp(hInst, IDB_RK);
		
	}
	if (board->SdPlayer() == color)
	{
		location.x = 4;
		location.y = 9;
	}
	else
	{
		location.x = 4;
		location.y = 0;
	}
}


KingPiece::~KingPiece(void)
{
}

BOOL KingPiece::Check(MoveStep* step)
{
	BOOL condition1 = step->dest.x >= 3 && step->dest.x <= 5;
	BOOL condition2 = FALSE;
	BOOL condition3 = FALSE;
	if(color != ChessApp::GetInstance()->GetSdPlayer())
	{
		condition2 = step->dest.y >= 0 && step->dest.y <= 2;
	}
	else
	{
		condition2 = step->dest.y >= 7 && step->dest.y <= 9;
	}
	int xd = abs(step->dest.x - step->src.x);
	int yd = abs(step->dest.y - step->src.y);
	if(xd > 1 || yd > 1)
	{
		condition3 = FALSE;
	}
	else
	{
		condition3 = (xd == 1 && yd == 0) || (yd == 1 && xd == 0);
	}

	return condition1 && condition2 && condition3;
}

int KingPiece::Count(void)
{
	return 1;
}

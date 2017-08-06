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
		name = " ø";
		bmpPiece = LoadResBmp(hInst, IDB_BA);

		location.x = 3;
		location.y = 0;
	}
	else
	{
		name = " À";
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
	return TRUE;
}

int AdvisorPiece::Count(void)
{
	return 2;
}
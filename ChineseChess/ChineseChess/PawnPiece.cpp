#include "stdafx.h"
#include "resource.h"
#include "Util.h"
#include "PawnPiece.h"


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

		location.x = 0;
		location.y = 3;
	}
	else
	{
		name = "±ø";
		bmpPiece = LoadResBmp(hInst, IDB_RP);

		location.x = 0;
		location.y = 6;
	}
}


PawnPiece::~PawnPiece(void)
{
}

BOOL PawnPiece::Check(MoveStep* step)
{
	return TRUE;
}

int PawnPiece::Count(void)
{
	return 5;
}

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
	:ChessPiece(board, hInst, color)
{
	new (this)CannonPiece(board);

	if(color == BACK)
	{
		name = "ез";
		bmpPiece = LoadResBmp(hInst, IDB_BC);

		location.x = 1;
		location.y = 2;
	}
	else
	{
		name = "ез";
		bmpPiece = LoadResBmp(hInst, IDB_RC);

		location.x = 1;
		location.y = 7;
	}
}


CannonPiece::~CannonPiece(void)
{
}

BOOL CannonPiece::Check(MoveStep* step)
{
	return TRUE;
}

int CannonPiece::Count(void)
{
	return 2;
}

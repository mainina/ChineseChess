#pragma once
#include "chesspiece.h"

class KnightPiece :
	public ChessPiece
{
public:
	KnightPiece(ChessBoard* board);
	KnightPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~KnightPiece(void);
	BOOL Check(MoveStep* step);
	int Count(void);
};


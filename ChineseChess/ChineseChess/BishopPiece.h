#pragma once
#include "chesspiece.h"
class BishopPiece :
	public ChessPiece
{
public:
	BishopPiece(ChessBoard* board);
	BishopPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~BishopPiece(void);
	BOOL Check(MoveStep* step);
	int Count(void);
};


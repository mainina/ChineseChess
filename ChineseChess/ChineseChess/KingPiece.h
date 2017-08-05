#pragma once
#include "chesspiece.h"
class KingPiece :
	public ChessPiece
{
public:
	KingPiece(ChessBoard* board);
	KingPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~KingPiece(void);
	BOOL Check(MoveStep* step);
	int Count(void);
};


#pragma once
#include "chesspiece.h"
#include <vector>

class AdvisorPiece :
	public ChessPiece
{
public:
	AdvisorPiece(ChessBoard* board);
	AdvisorPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~AdvisorPiece(void);
	BOOL Check(MoveStep* step);
	int Count(void);
};


#pragma once
#include "chesspiece.h"
class RookPiece :
	public ChessPiece
{
public:
	RookPiece(ChessBoard* board);
	RookPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~RookPiece(void);
	POINT Location(void);
	void SetLocation(POINT location);
	void SetLocation(LONG x, LONG y);
	HBITMAP Bmp(void);
	int Count(void);

	BOOL Check(MoveStep* step);
};


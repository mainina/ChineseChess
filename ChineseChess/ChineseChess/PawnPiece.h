#pragma once
#include "chesspiece.h"

class PawnPiece :
	public ChessPiece
{
public:
	PawnPiece(ChessBoard* board);
	PawnPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~PawnPiece(void);
	POINT Location(void);
	void SetLocation(POINT location);
	void SetLocation(LONG x, LONG y);
	HBITMAP Bmp(void);
	virtual int Count(void);

	virtual BOOL Check(MoveStep* step);
};


#pragma once
#include "chesspiece.h"
class CannonPiece :
	public ChessPiece
{
public:
	CannonPiece(ChessBoard* board);
	CannonPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~CannonPiece(void);
	POINT Location(void);
	void SetLocation(POINT location);
	void SetLocation(LONG x, LONG y);
	HBITMAP Bmp(void);
	virtual int Count(void);

	virtual BOOL Check(MoveStep* step);
};


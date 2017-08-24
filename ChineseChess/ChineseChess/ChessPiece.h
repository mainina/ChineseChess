#pragma once
#include "stdafx.h"
#include <string>
#include "Config.h"

class ChessBoard;

class ChessPiece
{
protected:
	ChessBoard* board;
	// 图片
	HBITMAP bmpPiece;
	// 标识
	int id;
	// 名称
	std::string name;
	// 颜色
	int color;
	POINT location;

public:
	ChessPiece(ChessBoard* board);
	ChessPiece(ChessBoard* board, HINSTANCE hInst, int color);
	~ChessPiece(void);
	POINT Location(void);
	void SetLocation(POINT location);
	void SetLocation(LONG x, LONG y);
	HBITMAP Bmp(void);
	int Color(void);
	virtual int Count(void) = 0;

	virtual BOOL Check(MoveStep* step) = 0;
};


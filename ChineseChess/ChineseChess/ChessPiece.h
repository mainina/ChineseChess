#pragma once
#include "stdafx.h"
#include <string>
#include "Config.h"

class ChessBoard;
class ChessApp;

class ChessPiece
{
protected:
	ChessBoard* board;
	// ͼƬ
	HBITMAP bmpPiece;
	// ��ʶ
	int id;
	// ����
	std::string name;
	// ��ɫ
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
	int Id() { return id; }
	virtual int Count(void) = 0;

	virtual BOOL Check(MoveStep* step) = 0;
};


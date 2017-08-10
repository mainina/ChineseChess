#pragma once
#include "Config.h"
#include "ChessPiece.h"
#include <vector>

class ChessBoard
{
private:
	HBITMAP bmpBoard;
	std::vector<ChessPiece*> pieceVector;

public:
	ChessBoard();
	~ChessBoard();
	void Startup(HINSTANCE hInstance);
	HDC DrawBoard(HDC hdc);
	HBITMAP Bmp(void);
	ChessPiece* FindPiece(int x, int y);
};


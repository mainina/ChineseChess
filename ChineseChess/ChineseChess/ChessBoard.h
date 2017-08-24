#pragma once
#include "Config.h"
#include "ChessPiece.h"
#include <vector>

class ChessBoard
{
private:
	int sdPlayer;
	HBITMAP bmpBoard;
	std::vector<ChessPiece*> pieceVector;

public:
	ChessBoard(void);
	~ChessBoard(void);

	void Startup(HINSTANCE hInstance, int iSdPlayer);
	HDC DrawBoard(HDC hdc);
	HBITMAP Bmp(void);
	int SdPlayer(void);
	void ChangeSide(void);
	void DelPiece(int sqY, int sqX);
	void MovePiece(MoveStep step);
	void MakeMove(MoveStep step);
	ChessPiece* FindPiece(int x, int y);
};


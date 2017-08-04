#pragma once
class ChessBoard
{
private:
	HBITMAP bmpBoard;

public:
	ChessBoard();
	~ChessBoard();
	void Startup(HINSTANCE hInstance);
	HDC DrawBoard(HDC hdc);
	HBITMAP Bmp(void);
};


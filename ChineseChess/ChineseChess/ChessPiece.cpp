#include "stdafx.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(ChessBoard* board)
{
	this->board = board;
}

ChessPiece::ChessPiece(ChessBoard* board, HINSTANCE hInst, int color)
{
	this->board = board;
	this->color = color;
}

ChessPiece::~ChessPiece(void)
{
}

POINT ChessPiece::Location(void)
{
	return location;
}

void ChessPiece::SetLocation(POINT location)
{
	this->location.x = location.x;
	this->location.y = location.y;
}

void ChessPiece::SetLocation(LONG x, LONG y)
{
	this->location.x = x;
	this->location.y = y;
}

HBITMAP ChessPiece::Bmp(void)
{
	return this->bmpPiece;
}

int ChessPiece::Color(void)
{
	return this->color;
}
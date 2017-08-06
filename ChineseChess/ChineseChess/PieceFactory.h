#pragma once
#include "ChessPiece.h"
#include "KingPiece.h"
#include "AdvisorPiece.h"
#include "BishopPiece.h"
#include "KnightPiece.h"
#include "RookPiece.h"
#include "CannonPiece.h"
#include "PawnPiece.h"

class PieceFactory
{
public:
	PieceFactory(void);
	~PieceFactory(void);
	static ChessPiece* Create(ChessBoard* board, HINSTANCE hInst, int color, int id, LONG x, LONG y)
	{
		ChessPiece* result = NULL;
		switch(id)
		{
		case PIECE_KING:
			result = new KingPiece(board, hInst, color);
			break;
		case PIECE_ADVISOR:
			result = new AdvisorPiece(board, hInst, color);
			break;
		case PIECE_BISHOP:
			result = new BishopPiece(board, hInst, color);
			break;
		case PIECE_KNIGHT:
			result = new KnightPiece(board, hInst, color);
			break;
		case PIECE_ROOK:
			result = new RookPiece(board, hInst, color);
			break;
		case PIECE_CANNON:
			result = new CannonPiece(board, hInst, color);
			break;
		case PIECE_PAWN:
			result = new PawnPiece(board, hInst, color);
			break;
		};
		if(x >= 0 && y >= 0)
		{
			result->SetLocation(x, y);
		}
		return result;
	};
};


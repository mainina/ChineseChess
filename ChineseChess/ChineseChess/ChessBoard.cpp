#include "stdafx.h"
#include "ChessBoard.h"
#include "Config.h"
#include "Util.h"
#include "resource.h"
#include "PieceFactory.h"


typedef std::vector<ChessPiece*> Vint;

ChessBoard::ChessBoard()
{
}


ChessBoard::~ChessBoard()
{
	if (!pieceVector.empty())
	{
		for (Vint::iterator it = pieceVector.begin(); it != pieceVector.end(); it++)
		{
			delete (*it);
		}
	}
}

void ChessBoard::Startup(HINSTANCE hInstance)
{
	bmpBoard = LoadResBmp(hInstance, IDB_BOARD);


	for (int i = 0; i <= PIECE_PAWN; i++)
	{
		for (int color = BACK; color <= RED; color++)
		{
			ChessPiece* piece = PieceFactory::Create(this, hInstance, color, i, -1, -1);
			pieceVector.push_back(piece);
			if (i <= PIECE_ROOK)
			{
				for (int j = 1; j < piece->Count(); j++)
				{
					// i * 2   对半分，规律
					ChessPiece* tmp = PieceFactory::Create(this, hInstance, color, i, piece->Location().x + (i * 2), piece->Location().y);
					pieceVector.push_back(tmp);
				}
			}
			else
			{
				if (i == PIECE_CANNON)
				{
					pieceVector.push_back(PieceFactory::Create(this, hInstance, color, i, 7, piece->Location().y));
				}
				else if (i == PIECE_PAWN)
				{
					LONG xx = piece->Location().x;
					for (int j = 1; j < piece->Count(); j++)
					{
						xx += 2;
						ChessPiece* tmp = PieceFactory::Create(this, hInstance, color, i, xx, piece->Location().y);
						pieceVector.push_back(tmp);
					}
				}
			}
		}
	}
}

HDC ChessBoard::DrawBoard(HDC hdc)
{
	int xx, yy;
	HDC hdcTmp;

	// 画棋盘
	hdcTmp = CreateCompatibleDC(hdc);
	SelectObject(hdcTmp, bmpBoard);
	BitBlt(hdc, 0, 0, BOARD_WIDTH, BOARD_HEIGHT, hdcTmp, 0, 0, SRCCOPY);

	// 画棋子
	for (Vint::iterator it = pieceVector.begin(); it != pieceVector.end(); it++)
	{
		xx = BOARD_EDGE + (*it)->Location().x * SQUARE_SIZE;
		yy = BOARD_EDGE + (*it)->Location().y * SQUARE_SIZE;
		DrawTransBmp(hdc, hdcTmp, xx, yy, (*it)->Bmp());
	}

	return hdcTmp;
}

HBITMAP ChessBoard::Bmp(void)
{
	return bmpBoard;
}

ChessPiece * ChessBoard::FindPiece(int x, int y)
{
	return nullptr;
}

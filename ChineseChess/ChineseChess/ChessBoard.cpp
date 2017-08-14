#include "stdafx.h"
#include "resource.h"
#include "Config.h"
#include "Util.h"
#include "PieceFactory.h"
#include "ChessBoard.h"

typedef std::vector<ChessPiece*> Vint;

ChessBoard::ChessBoard(void)
{
}


ChessBoard::~ChessBoard(void)
{
	if(!pieceVector.empty())
	{
		for(Vint::iterator it = pieceVector.begin(); it != pieceVector.end();it++)
		{
			delete (*it);
		}
	}
}

void ChessBoard::Startup(HINSTANCE hInstance)
{
	sdPlayer = RED;
	bmpBoard = LoadResBmp(hInstance, IDB_BOARD);

	for(int i = 0; i <= PIECE_PAWN; i++)
	{
		for(int color = BACK; color <= RED; color++)
		{
			ChessPiece* piece = PieceFactory::Create(this, hInstance, color, i, -1, -1);
			pieceVector.push_back(piece);
			if(i <= PIECE_ROOK)
			{
				for(int j = 1; j < piece->Count(); j++)
				{
					// i * 2   对半分，规律
					ChessPiece* tmp = PieceFactory::Create(this, hInstance, color, i, piece->Location().x + (i * 2), piece->Location().y);
					pieceVector.push_back(tmp);
				}
			}
			else
			{
				if( i == PIECE_CANNON)
				{
					pieceVector.push_back(PieceFactory::Create(this, hInstance, color, i, 7, piece->Location().y));
				}
				else if(i == PIECE_PAWN)
				{
					LONG xx = piece->Location().x;
					for(int j = 1; j < piece->Count(); j++)
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

	for(Vint::iterator it = pieceVector.begin(); it != pieceVector.end();it++)
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

int ChessBoard::SdPlayer(void)
{
	return this->sdPlayer;
}

ChessPiece* ChessBoard::FindPiece(int x, int y)
{
	for(Vint::iterator it = pieceVector.begin(); it != pieceVector.end(); it++)
	{
		if((*it)->Location().x == x && (*it)->Location().y == y)
		{
			return (*it);
		}
	}
	return NULL;
}

void ChessBoard::ChangeSide(void)
{
	sdPlayer = 1 - sdPlayer;
}

void ChessBoard::DelPiece(int sqY, int sqX)
{
	for(Vint::iterator it = pieceVector.begin(); it != pieceVector.end(); it++)
	{
		if((*it)->Location().x == sqX && (*it)->Location().y == sqY)
		{
			pieceVector.erase(it);
			break;
		}
	}
}

void ChessBoard::MovePiece(MoveStep step)
{
	/*DelPiece(step.dest.y, step.dest.x);
	int pc = ucpcSquares[step.src.y][step.src.x];
	DelPiece(step.src.y, step.src.x);
	AddPiece(step.dest.y, step.dest.x, pc);*/
}

void ChessBoard::MakeMove(MoveStep step)
{
	MovePiece(step);
	ChangeSide();
}
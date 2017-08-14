#pragma once
#include "stdafx.h"

const int MAX_ROW_NUM = 10;
const int MAX_COLUMN_NUM = 9;

// ºÚÉ«
static const int BACK = 0;
// ºìÉ«
static const int RED = 1;

const int WINDOW_STYLES = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
const int MASK_COLOR = RGB(0, 255, 0);
const int SQUARE_SIZE = 56;
const int BOARD_EDGE = 8;
const int BOARD_WIDTH = BOARD_EDGE + SQUARE_SIZE * 9 + BOARD_EDGE;
const int BOARD_HEIGHT = BOARD_EDGE + SQUARE_SIZE * 10 + BOARD_EDGE;

const int PIECE_KING = 0;
const int PIECE_ADVISOR = 1;
const int PIECE_BISHOP = 2;
const int PIECE_KNIGHT = 3;
const int PIECE_ROOK = 4;
const int PIECE_CANNON = 5;
const int PIECE_PAWN = 6;

class MoveStep
{
public:
	POINT src, dest;
	MoveStep(LONG srcX, LONG srcY, LONG destX, LONG destY)
	{
		this->src.x = srcX;
		this->src.y = srcY;
		this->dest.x = destX;
		this->dest.y = destY;
	}
	~MoveStep(void)
	{
	}
	void Init()
	{
		src.x = 0;
		src.y = 0;
		dest.x = 0;
		dest.y = 0;
	}

	void SetStep(MoveStep step)
	{
		this->src = step.src;
		this->dest = step.dest;
	}

	BOOL IsInit()
	{
		return 0 == src.x && src.x == src.y && dest.x == dest.y && src.x == dest.x;
	}
};
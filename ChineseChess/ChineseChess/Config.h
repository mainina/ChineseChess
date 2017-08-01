#pragma once
#include "stdafx.h"

// 棋盘的垂直边界
const int MAX_ROW_NUM = 10;
// 棋盘的水平边界
const int MAX_COLUMN_NUM = 9;

// 黑色
static const int BACK = 0;
// 红色
static const int RED = 1;

const int WINDOW_STYLES = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
// 选择图片的颜色值，做透明处理用
const int MASK_COLOR = RGB(0, 255, 0);
// 棋盘上一小格的连长
const int SQUARE_SIZE = 56;
const int BOARD_EDGE = 8;
const int BOARD_WIDTH = BOARD_EDGE + SQUARE_SIZE * 9 + BOARD_EDGE;
const int BOARD_HEIGHT = BOARD_EDGE + SQUARE_SIZE * 10 + BOARD_EDGE;

// 帅或将
const int PIECE_KING = 0;
// 仕或士
const int PIECE_ADVISOR = 1;
// 相或象
const int PIECE_BISHOP = 2;
// 马
const int PIECE_KNIGHT = 3;
// 车
const int PIECE_ROOK = 4;
// 炮
const int PIECE_CANNON = 5;
// 兵
const int PIECE_PAWN = 6;

// 一步棋的记录
class MoveStep
{
public:
	// 起点、终点
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
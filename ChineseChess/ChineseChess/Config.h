#pragma once
#include "stdafx.h"

// ���̵Ĵ�ֱ�߽�
const int MAX_ROW_NUM = 10;
// ���̵�ˮƽ�߽�
const int MAX_COLUMN_NUM = 9;

// ��ɫ
static const int BACK = 0;
// ��ɫ
static const int RED = 1;

const int WINDOW_STYLES = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
// ѡ��ͼƬ����ɫֵ����͸��������
const int MASK_COLOR = RGB(0, 255, 0);
// ������һС�������
const int SQUARE_SIZE = 56;
const int BOARD_EDGE = 8;
const int BOARD_WIDTH = BOARD_EDGE + SQUARE_SIZE * 9 + BOARD_EDGE;
const int BOARD_HEIGHT = BOARD_EDGE + SQUARE_SIZE * 10 + BOARD_EDGE;

// ˧��
const int PIECE_KING = 0;
// �˻�ʿ
const int PIECE_ADVISOR = 1;
// �����
const int PIECE_BISHOP = 2;
// ��
const int PIECE_KNIGHT = 3;
// ��
const int PIECE_ROOK = 4;
// ��
const int PIECE_CANNON = 5;
// ��
const int PIECE_PAWN = 6;

// һ����ļ�¼
class MoveStep
{
public:
	// ��㡢�յ�
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
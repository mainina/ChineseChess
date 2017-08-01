#include "stdafx.h"
#include "Config.h"

// 加载资源文件中的图片
static HBITMAP LoadResBmp(HINSTANCE hInst, int nResId)
{
	return (HBITMAP) LoadImage(hInst, MAKEINTRESOURCE(nResId), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
}

// 绘制透明图片
static void DrawTransBmp(HDC hdc, HDC hdcTmp, int xx, int yy, HBITMAP bmp) {
	SelectObject(hdcTmp, bmp);
	TransparentBlt(hdc, xx, yy, SQUARE_SIZE, SQUARE_SIZE, hdcTmp, 0, 0, SQUARE_SIZE, SQUARE_SIZE, MASK_COLOR);
}
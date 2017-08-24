#include "stdafx.h"
#include "Config.h"
#include <string>
#include <locale.h> 

static HBITMAP LoadResBmp(HINSTANCE hInst, int nResId)
{
	return (HBITMAP) LoadImage(hInst, MAKEINTRESOURCE(nResId), IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
}

// »æÖÆÍ¸Ã÷Í¼Æ¬
static void DrawTransBmp(HDC hdc, HDC hdcTmp, int xx, int yy, HBITMAP bmp) {
	SelectObject(hdcTmp, bmp);
	TransparentBlt(hdc, xx, yy, SQUARE_SIZE, SQUARE_SIZE, hdcTmp, 0, 0, SQUARE_SIZE, SQUARE_SIZE, MASK_COLOR);
}

static std::string ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	std::string r(len, '\0');
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, &r[0], len, 0, 0);
	return r;
}
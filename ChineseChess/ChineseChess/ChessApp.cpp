#include "stdafx.h"
#include "Config.h"
#include "resource.h"
#include "Util.h"
#include "ChessApp.h"


ChessApp::ChessApp(void)
{
	cBoard = new ChessBoard();
	mvLast = new MoveStep(0, 0, 0, 0);
	sqSelected.x = -1;
	sqSelected.y = -1;
}


ChessApp::~ChessApp(void)
{
	if(cBoard != NULL)
	{
		delete cBoard;
	}
	if(mvLast != NULL)
	{
		delete mvLast;
	}
}

ChessApp* ChessApp::instance = new ChessApp();
ChessApp* ChessApp::GetInstance()
{
	return instance;
}

void ChessApp::Startup(int iSdPlayer)
{
	sdPlayer = iSdPlayer;
	bmpSelected = LoadResBmp(hInst, IDB_SELECTED);
	cBoard->Startup(hInst, iSdPlayer);
	mvLast->Init();
}

BOOL ChessApp::IsSelected(void)
{
	return sqSelected.x >= 0 && sqSelected.y >= 0;
}

void ChessApp::SetUser(LoginCmdData * iUser)
{
	user.SetUserName(iUser->GetUser());
	user.SetToken(iUser->GetToken());
}

int ChessApp::GetSdPlayer()
{
	return this->sdPlayer;
}

void ChessApp::NotSelect(void)
{
	sqSelected.x = -1;
	sqSelected.y = -1;
}

void ChessApp::DrawBoard(HDC hdc)
{
	HDC hdcTmp =	cBoard->DrawBoard(hdc);
	if(IsSelected())
	{
		int xx = BOARD_EDGE + sqSelected.x * SQUARE_SIZE;
		int yy = BOARD_EDGE + sqSelected.y * SQUARE_SIZE;
		DrawTransBmp(hdc, hdcTmp, xx, yy, bmpSelected);
	}
	DeleteDC(hdcTmp);
}

// 绘制格子
void ChessApp::DrawSquare(POINT pieceLocation, BOOL bSelected = FALSE) {
	int xx, yy;

	xx = BOARD_EDGE + pieceLocation.x * SQUARE_SIZE;
	yy = BOARD_EDGE + pieceLocation.y * SQUARE_SIZE;
	SelectObject(hdcTmp, cBoard->Bmp());
	BitBlt(hdc, xx, yy, SQUARE_SIZE, SQUARE_SIZE, hdcTmp, xx, yy, SRCCOPY);

	ChessPiece* piece = cBoard->FindPiece(pieceLocation.x, pieceLocation.y);
	if (piece != NULL) {
		DrawTransBmp(hdc, hdcTmp, xx, yy, piece->Bmp());
	}
	if (bSelected) {
		DrawTransBmp(hdc, hdcTmp, xx, yy, bmpSelected);
	}
}

void ChessApp::Click(int x, int y)
{
	ChessPiece* piece = cBoard->FindPiece(x, y);
	ChessPiece* selectedPiece = cBoard->FindPiece(sqSelected.x, sqSelected.y);
	// 如果选择的子，是对方的
	if(piece != NULL && piece->Color() != cBoard->SdPlayer())
	{
		// 如果没有点击子，　或者已点击的子不是已方子
		if(!(selectedPiece != NULL && selectedPiece->Color() == cBoard->SdPlayer()))
		{
			return;
		}
	}
	if(piece == NULL && selectedPiece != NULL && selectedPiece->Color() != cBoard->SdPlayer())
	{
		return;
	}

	hdc = GetDC(hWnd);
	hdcTmp = CreateCompatibleDC(hdc);

	if(IsSelected())
	{
		// 选择的位置有子
		if(piece != NULL)
		{
			// 选择是自己的子
			if(piece->Color() == cBoard->SdPlayer())
			{
				DrawSquare(sqSelected);
				sqSelected.x = x;
				sqSelected.y = y;
				DrawSquare(sqSelected, IsSelected());
			}else{
				// 对方
				MoveStep step(sqSelected.x, sqSelected.y, x, y);
				if(selectedPiece->Check(&step)){
					cBoard->DelPiece(y, x);
					selectedPiece->SetLocation(x, y);
					DrawSquare(sqSelected, TRUE);

					sqSelected.x = x;
					sqSelected.y = y;
					DrawSquare(sqSelected, TRUE);

					if(!mvLast->IsInit())
					{
						DrawSquare(mvLast->src);
					}
					mvLast->SetStep(step);
					cBoard->ChangeSide();
				}
				else
				{
					ShowDialog();
				}
			}
		}else{ // 选择的位置没有子
			MoveStep step(sqSelected.x, sqSelected.y, x, y);
			if(selectedPiece->Check(&step)){

				selectedPiece->SetLocation(x, y);
				DrawSquare(sqSelected, TRUE);

				sqSelected.x = x;
				sqSelected.y = y;
				DrawSquare(sqSelected, TRUE);

				if(!mvLast->IsInit())
				{
					DrawSquare(mvLast->src);
				}
				mvLast->SetStep(step);
				cBoard->ChangeSide();
			}
			else
			{
				ShowDialog();
			}
		}
	}
	else
	{
		//　还没有选中任何子
		if(piece != NULL && piece->Color() == cBoard->SdPlayer())
		{
			sqSelected.x = x;
			sqSelected.y = y;
			DrawSquare(sqSelected, TRUE);
		}
	}

	DeleteDC(hdcTmp);
	ReleaseDC(hWnd, hdc);
}

void ChessApp::ShowDialog(void)
{
	TCHAR errorTitle[100];
	LoadString(hInst, IDS_ERROR_CONTENT, errorTitle, 100);
	TCHAR errorContent[100];
	LoadString(hInst, IDS_ERROR_TITLE, errorContent, 100);
	MessageBox(GetForegroundWindow(), errorTitle, errorContent, 1);  
}
// ChineseChess.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ChineseChess.h"
#include "ChessApp.h"
#include "ClientSocket.h"
#include "Util.h"
#include "CmdData.h"
#include <functional>

#define MAX_LOADSTRING 100

// 全局变量:
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Login(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

static ChessApp* app = ChessApp::GetInstance();
static ClientSocket clientSocket;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	app->hInst = hInstance;
	//app->Startup();

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CHINESECHESS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	// 开启线程，连接服务器
	if (clientSocket.Init() == 0)
	{
		clientSocket.Start();
	}

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHINESECHESS));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_XQWIZARD));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_CHINESECHESS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	// WS_OVERLAPPEDWINDOW
	app->hWnd = CreateWindow(szWindowClass, szTitle, WINDOW_STYLES,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!app->hWnd)
	{
		return FALSE;
	}

	ShowWindow(app->hWnd, nCmdShow);
	UpdateWindow(app->hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	int x, y;

	switch (message)
	{
	case WM_CREATE:
		GetWindowRect(hWnd, &rect);

		rect.right = rect.left + BOARD_WIDTH;
		rect.bottom = rect.top + BOARD_HEIGHT;
		x = (GetSystemMetrics(SM_CXSCREEN) - rect.right) / 2;
		y = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) / 2;

		AdjustWindowRect(&rect, WINDOW_STYLES, TRUE);
		MoveWindow(hWnd, x, y, rect.right - rect.left, rect.bottom - rect.top, TRUE);

		DialogBox(app->hInst, MAKEINTRESOURCE(IDD_lOGINbOX), hWnd, Login);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(app->hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			clientSocket.Close();
			DestroyWindow(hWnd);
			break;
		case IDB_START:
			clientSocket.GoToWar();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		app->DrawBoard(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		x = (LOWORD(lParam) - BOARD_EDGE) / SQUARE_SIZE;
		y = (HIWORD(lParam) - BOARD_EDGE) / SQUARE_SIZE;
		if (x >= 0 && x <= MAX_COLUMN_NUM && y >= 0 && y <= MAX_ROW_NUM) {
			app->Click(x, y);
		}
		break;
	case WM_DESTROY:
		clientSocket.Close();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

HWND loginDlg;
void LoginCallback(CmdData* cmdData)
{
	if (cmdData->IsOk())
	{
		app->SetUser((LoginCmdData*)cmdData);
		EndDialog(loginDlg, TRUE);
	}
	else
	{
		SetDlgItemText(loginDlg, IDC_ERROR_INFO, L"登录失败");
	}
}

// “登录”框的消息处理程序。
INT_PTR CALLBACK Login(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SendDlgItemMessage(hDlg,
			IDE_PASSWORDEDIT,
			EM_SETPASSWORDCHAR,
			(WPARAM) '*',
			(LPARAM)0);

		// Set the default push button to "Cancel." 
		SendMessage(hDlg,
			DM_SETDEFID,
			(WPARAM)IDCANCEL,
			(LPARAM)0);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			loginDlg = hDlg;

			TCHAR szBuf[40];
			GetDlgItemText(hDlg, IDC_USERNAME, szBuf, 39);
			std::wstring userName(szBuf);
			GetDlgItemText(hDlg, IDE_PASSWORDEDIT, szBuf, 39);
			std::wstring pwd(szBuf);
			clientSocket.Login(ws2s(userName), ws2s(pwd), LoginCallback);

			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			clientSocket.Close();
			exit(0);
			return (INT_PTR)TRUE;
		}
		break;
	case WM_CTLCOLORSTATIC:
		// Set the colour of the text for our URL
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_ERROR_INFO))
		{
			// we're about to draw the static
			// set the text colour in (HDC)lParam
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, RGB(255, 0, 0));
			// NOTE: per documentation as pointed out by selbie, GetSolidBrush would leak a GDI handle.
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		break;
	}
	return (INT_PTR)FALSE;
}


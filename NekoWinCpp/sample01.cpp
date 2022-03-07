/* sample01.cpp */

#include "framework.h"
#include "NekoWinCpp.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// グローバル文字列を初期化する
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_NEKOWINCPP, szWindowClass, MAX_LOADSTRING);

	if (!MyRegisterClass(hInstance)) return FALSE;
	if (!InitInstance(hInstance, nCmdShow)) return FALSE;

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NEKOWINCPP));

	MSG msg;
	BOOL bRet;

	while ((bRet = GetMessage(&msg, NULL, 0, 0) != 0))
	{
		if (bRet == -1)
		{
			break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


// ウィンドウクラスの登録
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEXW);               // 構造体サイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;           // クラスのスタイル
	wcex.lpfnWndProc = WndProc;                     // プロシージャ名
	wcex.cbClsExtra = 0;                            // 補助メモリ
	wcex.cbWndExtra = 0;                            // 補助メモリ
	wcex.hInstance = hInstance;                     // インスタンス
	wcex.hIcon = LoadIcon(
		hInstance, 
		MAKEINTRESOURCE(IDI_NEKOWINCPP));         // アイコン
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);  // カーソル
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// 背景ブラシ
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_NEKOWINCPP);    // メニュー名
	wcex.lpszClassName = szWindowClass;                      // クラス名
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 小アイコン
	

	return (RegisterClassExW(&wcex));
}


// ウィンドウの生成
BOOL InitInstance(HINSTANCE hInstance, int nCmdLine)
{

	hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

	HWND hWnd = CreateWindowW(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // X
		CW_USEDEFAULT, // Y
		CW_USEDEFAULT, // W
		CW_USEDEFAULT, // H
		nullptr, // 親ウィンドウのハンドル
		nullptr, // メニューハンドル、クラスメニューを使うときはNULL
		hInstance, // インスタンスハンドル
		nullptr // ウィンドウ作成データ
		);

	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdLine);
	UpdateWindow(hWnd);
	return TRUE;
}


// バージョン情報ボックスのメッセージ ハンドラー
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


// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, message, wParam, lParam));
	}

	return 0;
}


/**
 *@file   Windows06.cpp
 *@author Y.Kishimoto
 *@date   31.Mar.2019
 * 基本のウィンドウズプログラム
 */

#include "main.h"
#include "framework.h"
#include "Common.h"
#include "Card.h"
#include <crtdbg.h>
#include <tchar.h>
#include <stdio.h>
#include <d2d1.h>   //!< Direct2D に必要
#include <wincodec.h>

#pragma comment(lib,"d2d1.lib")    //!< direct2d に必要

ID2D1Factory* g_pD2DFactory = NULL;      //  D2D1Factoryオブジェクト
ID2D1HwndRenderTarget* g_pRenderTarget = NULL;    //  描画ターゲット
ID2D1Bitmap* g_pBG = NULL;
ID2D1Bitmap* g_pFG = NULL;
Card* g_pCard;


#define FPS         30
#define INTERVAL    (1.0/FPS)
double  g_dblDenominator;
double  g_dblFrame;
double g_deltaTime;
__int64 g_i64OldTimer;

double timer = 0;
int warpCount = 0;

//! 関数 WndProc のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

/**
 *@fn
 *@brief アプリケーションのエントリーポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	//! デバッグ用フラグのセット
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//! 変数宣言
	WNDCLASSEX wcex;  //  ウィンドウクラス構造体
	HWND hWnd;        //  ウィンドウハンドル
	RECT    bounds, client;  //  RECT 構造体

	//  (1)初期化部分
	CoInitialize(NULL);

	//  (1)-a ウィンドウクラスの登録
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;  //  ウィンドウプロシージャの登録
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;  //  アプリケーションインスタンス
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("Windows06");  //  ウィンドウクラス名
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wcex);

	//  (1)-b ウィンドウの生成
	hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wcex.lpszClassName, _T("Windows01"),
		WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, 0, WINDOW_WIDTH,WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;

	//  ウィンドウサイズの調整
	//  ここは無くても動く
	GetWindowRect(hWnd, &bounds);
	GetClientRect(hWnd, &client);
	MoveWindow(hWnd, bounds.left, bounds.top,
		WINDOW_WIDTH * 2 - client.right,
		WINDOW_HEIGHT * 2 - client.bottom,
		false);

	//  ウィンドウの再表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//  再表示の際、WndProc が呼び出される事にも注意！

	//  Direct2D 初期化
	{
		HRESULT hr;
		//  Direct2D Factory の生成
		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
		GetClientRect(hWnd, &client);
		D2D1_SIZE_U size = D2D1::SizeU(
			client.right - client.left,
			client.bottom - client.top
		);

		//  Direct2D 描画ターゲットの生成
		hr = g_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&g_pRenderTarget
		);
	}
	{
		//  画像の読み込み

		D2D1_BITMAP_PROPERTIES bitmapProperties;
		bitmapProperties.dpiX = 96.0f;
		bitmapProperties.dpiY = 96.0f;
		bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

		POINT point = { 0,0 };
		g_pCard = new Card((float)0.25, point,
							bitmapProperties
							);
	}
	InvalidateRect(hWnd, NULL, false);

	::QueryPerformanceCounter((LARGE_INTEGER*)& g_i64OldTimer);
	__int64    i64Tmp;
	::QueryPerformanceFrequency((LARGE_INTEGER*)& i64Tmp);
	g_dblDenominator = 1.0 / (double)i64Tmp;
	g_dblFrame = 0.0f;

	//  (2)メッセージループ
	MSG    msg;
	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (timer > 3.0f) {
				warpCount++;
				POINT warpTarget = { warpCount * 100,warpCount * 100 };
				g_pCard->Warp(warpTarget);
				timer = 0;
			}

			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

			double    t;

			::QueryPerformanceCounter((LARGE_INTEGER*)& i64Tmp);

			t = (i64Tmp - g_i64OldTimer) * g_dblDenominator;
			g_i64OldTimer = i64Tmp;
			g_dblFrame += t;
			g_deltaTime = t;
			timer += t;

			if (g_dblFrame >= INTERVAL) {
				int    c = (int)(g_dblFrame / INTERVAL);
				g_dblFrame -= INTERVAL * c;
				InvalidateRect(hWnd, NULL, false);
			}

		}
	}

	//  (3)終了処理
	if (g_pBG) {
		g_pBG->Release();
		g_pBG = NULL;
	}
	if (g_pFG) {
		g_pFG->Release();
		g_pFG = NULL;
	}

	g_pRenderTarget->Release();  //!< RenderTarget の破棄
	g_pRenderTarget = NULL;

	g_pD2DFactory->Release(); //!< ファクトリーの解放
	g_pD2DFactory = NULL;

	g_pCard->Release();
	g_pCard = NULL;

	CoUninitialize();
	return (int)msg.wParam;

}


/**
 *@fn
 * ウインドウに渡されたイベントのハンドラ
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:  //  画面再描画イベント
		if (g_pRenderTarget != NULL) {
			g_pRenderTarget->BeginDraw();  //!< 描画開始

			g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); //!< Transform の設定

			g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkBlue));   //!< 画面のクリア
		

			//if (g_pBG != NULL) {
			//	D2D1_SIZE_U sz = g_pBG->GetPixelSize();
			//	D2D1_RECT_F drc, src;
			//	D2D1_SIZE_F ssz = g_pRenderTarget->GetSize();
			//	drc.left = 0;
			//	drc.top = 0;
			//	drc.right = drc.left + ssz.width;
			//	drc.bottom = drc.top + ssz.height;
			//	src.left = 0;
			//	src.top = 0;
			//	src.right = sz.width;
			//	src.bottom = sz.height;
			//	g_pRenderTarget->DrawBitmap(g_pBG, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
			//}

			//if (g_pFG != NULL) {
			//	D2D1_SIZE_U sz = g_pFG->GetPixelSize();
			//	D2D1_RECT_F drc, src;
			//	drc.left = 0;
			//	drc.top = 0;
			//	drc.right = drc.left + sz.width;
			//	drc.bottom = drc.top + sz.height;
			//	src.left = 0;
			//	src.top = 0;
			//	src.right = sz.width;
			//	src.bottom = sz.height;
			//	g_pRenderTarget->DrawBitmap(g_pFG, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
			//}

			g_pCard->Draw(g_pRenderTarget);

			g_pRenderTarget->EndDraw();  //  描画終了
		}

		ValidateRect(hWnd, NULL);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return    0;
}
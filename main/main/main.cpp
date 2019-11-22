/**
 *@file   Windows06.cpp
 *@author Y.Kishimoto
 *@date   31.Mar.2019
 * 基本のウィンドウズプログラム
 */

#include "main.h"
#include "framework.h"
#include "Common.h"

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
		IWICImagingFactory* pFactory = NULL;
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrame = NULL;
		IWICFormatConverter* pFormatConverter = NULL;
		WICPixelFormatGUID pixelFormat;

		D2D1_BITMAP_PROPERTIES bitmapProperties;
		bitmapProperties.dpiX = 96.0f;
		bitmapProperties.dpiY = 96.0f;
		bitmapProperties.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
		bitmapProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

		HRESULT hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pFactory)
		);
		if (SUCCEEDED(hr)) {
			//  jpg ファイル test.jpg の読み込み
			hr = pFactory->CreateDecoderFromFilename(L"res\\BackGround.jpg", 0,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			if (SUCCEEDED(hr)) {
				hr = pDecoder->GetFrame(0, &pFrame);
				//  Get the pixel format of the image
				hr = pFrame->GetPixelFormat(&pixelFormat);
				if (SUCCEEDED(hr) && pixelFormat == GUID_WICPixelFormat32bppBGRA) {
					//    読みこんだ画像が、32bit BGRA であれば、変換不要
					hr = g_pRenderTarget->CreateBitmapFromWicBitmap(
						pFrame,
						&bitmapProperties,
						&g_pBG
					);
				}

				else if (SUCCEEDED(hr)) {
					hr = pFactory->CreateFormatConverter(&pFormatConverter);
					if (SUCCEEDED(hr)) {
						hr = pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
						if (SUCCEEDED(hr)) {
							hr = g_pRenderTarget->CreateBitmapFromWicBitmap(
								pFormatConverter,
								&bitmapProperties,
								&g_pBG
							);
						}
						pFormatConverter->Release();
						pFormatConverter = NULL;
					}
					pFrame->Release();
					pFrame = NULL;
				}
				pDecoder->Release();
				pDecoder = NULL;
			}

			//  png ファイルの読み込み
			hr = pFactory->CreateDecoderFromFilename(L"res\\torannpu-illust49.png", 0,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			if (SUCCEEDED(hr)) {
				hr = pDecoder->GetFrame(0, &pFrame);
				if (SUCCEEDED(hr)) {
					hr = pFactory->CreateFormatConverter(&pFormatConverter);
					if (SUCCEEDED(hr)) {
						hr = pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
						if (SUCCEEDED(hr)) {

							D2D1_SIZE_U sizBitmap;
							UINT width, height;
							pFrame->GetSize(&width, &height);
							sizBitmap.width = width;
							sizBitmap.height = height;
							hr = g_pRenderTarget->CreateBitmap(sizBitmap, bitmapProperties, &g_pFG);
							if (SUCCEEDED(hr)) {
								BYTE* pBuffer = new BYTE[4 * width * height];
								double frac = 1.0 / 255.0;
								double a;
								pFormatConverter->CopyPixels(NULL, width * 4, width * 4 * height, pBuffer);
								for (int row = 0; row < height; ++row) {
									BYTE* p = pBuffer + (width * 4) * row;
									for (int col = 0; col < width; ++col) {
										a = frac * p[3];
										p[0] = (BYTE)(a * p[0]);
										p[1] = (BYTE)(a * p[1]);
										p[2] = (BYTE)(a * p[2]);
										p += 4;
									}
								}
								g_pFG->CopyFromMemory(NULL, pBuffer, width * 4);
								delete[] pBuffer;
							}


						}
						pFormatConverter->Release();
						pFormatConverter = NULL;
					}
					pFrame->Release();
					pFrame = NULL;
				}
				pDecoder->Release();
				pDecoder = NULL;
			}
			pFactory->Release();
			pFactory = NULL;
		}
	}
	InvalidateRect(hWnd, NULL, false);

	//  (2)メッセージループ
	MSG        msg;
	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
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

			if (g_pBG != NULL) {
				D2D1_SIZE_U sz = g_pBG->GetPixelSize();
				D2D1_RECT_F drc, src;
				D2D1_SIZE_F ssz = g_pRenderTarget->GetSize();
				drc.left = 0;
				drc.top = 0;
				drc.right = drc.left + ssz.width;
				drc.bottom = drc.top + ssz.height;
				src.left = 0;
				src.top = 0;
				src.right = sz.width;
				src.bottom = sz.height;
				g_pRenderTarget->DrawBitmap(g_pBG, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
			}

			if (g_pFG != NULL) {
				D2D1_SIZE_U sz = g_pFG->GetPixelSize();
				D2D1_RECT_F drc, src;
				drc.left = 0;
				drc.top = 0;
				drc.right = drc.left + sz.width * DEFAULT_CARD_SIZE;
				drc.bottom = drc.top + sz.height * DEFAULT_CARD_SIZE;
				src.left = 0;
				src.top = 0;
				src.right = sz.width;
				src.bottom = sz.height;
				g_pRenderTarget->DrawBitmap(g_pFG, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);
			}

			g_pRenderTarget->EndDraw();  //  描画終了
		}
		ValidateRect(hWnd, NULL);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return    0;
}
#include "Card.h"
#include "Common.h"
#include "Time.h"
#include <wincodec.h>
#include <d2d1.h>

#pragma comment(lib,"d2d1.lib")
#define CARD_MOVE_DECAY 0.8


extern Time* g_pTime;
extern ID2D1HwndRenderTarget* g_pRenderTarget;
extern ID2D1Factory* g_pFactory;
Card::Card(float scale, POINT point,
		D2D1_BITMAP_PROPERTIES bitmapProperties
) {
	mScale = scale;
	beforeMovePoint = nowPoint = point;

	{
		IWICImagingFactory* pFactory = NULL;
		HRESULT hr;
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrame = NULL;
		IWICFormatConverter* pFormatConverter = NULL;
		WICPixelFormatGUID pixelFormat;

		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&pFactory)
		);
		if (SUCCEEDED(hr)) 
		{
			if (backPicture == NULL) 
			{
				//  png ファイルの読み込み
				hr = pFactory->CreateDecoderFromFilename(L"res\\Back.png", 0,
					GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
				if (SUCCEEDED(hr)) {
					hr = pDecoder->GetFrame(0, &pFrame);
					if (SUCCEEDED(hr)) {
						hr = pFactory->CreateFormatConverter(&pFormatConverter);
						if (SUCCEEDED(hr)) {
							hr = pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
							if (SUCCEEDED(hr)) {

								UINT width, height;
								pFrame->GetSize(&width, &height);
								backPictureSize.width = width;
								backPictureSize.height = height;
								hr = g_pRenderTarget->CreateBitmap(backPictureSize, bitmapProperties,&backPicture);
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
									backPicture->CopyFromMemory(NULL, pBuffer, width * 4);
									delete[] pBuffer;
								}
							}
							pFormatConverter->Release();
						}
						pFrame->Release();
					}
					pDecoder->Release();
				}
			}

			//  png ファイルの読み込み
			hr = pFactory->CreateDecoderFromFilename(L"res\\Spade1.png", 0,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			if (SUCCEEDED(hr)) {
				hr = pDecoder->GetFrame(0, &pFrame);
				if (SUCCEEDED(hr)) {
					hr = pFactory->CreateFormatConverter(&pFormatConverter);
					if (SUCCEEDED(hr)) {
						hr = pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom);
						if (SUCCEEDED(hr)) {

							UINT width, height;
							pFrame->GetSize(&width, &height);
							frontPictureSize.width = width;
							frontPictureSize.height = height;
							hr = g_pRenderTarget->CreateBitmap(frontPictureSize, bitmapProperties, &frontPicture);
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
								frontPicture->CopyFromMemory(NULL, pBuffer, width * 4);
								delete[] pBuffer;
							}
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


Card::~Card()
{
}

void Card::Release() 
{
	if(frontPicture != NULL)frontPicture->Release(); frontPicture = NULL;
	if(backPicture != NULL)backPicture->Release(); backPicture = NULL;
}


void Card::Draw(ID2D1HwndRenderTarget* g_pRenderTarget) 
{
	ID2D1Bitmap* drawnPicture;		// 描画する画像
	D2D1_SIZE_U drawnPictureSize;	// 画像データの縦横の大きさ

	if (isFront) 
	{
		drawnPicture = frontPicture;
		drawnPictureSize = frontPictureSize;
	}
	else 
	{
		drawnPicture = backPicture;
		drawnPictureSize = backPictureSize;
	}

	D2D1_RECT_F drc, src;
	drc.left = nowPoint.x;
	drc.top = nowPoint.y;
	drc.right = drc.left + drawnPictureSize.width * mScale;
	drc.bottom = drc.top + drawnPictureSize.height * mScale;
	src.left = 0;
	src.top = 0;
	src.right = drawnPictureSize.width;
	src.bottom = drawnPictureSize.height;
	g_pRenderTarget->DrawBitmap(drawnPicture, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

}

void Card::SetTargetPoint(POINT targetPoint) 
{
	this->targetPoint = targetPoint;
	isMoving = true;
}

void Card::Move(float size) 
{
	LARGE_INTEGER deltaTime;
	deltaTime = g_pTime->GetDeltaTime();
	moveTime.QuadPart += deltaTime.QuadPart;
	
}

void Card::Warp(POINT target) {
	beforeMovePoint = nowPoint = target;
}

void Card::TurnOver() 
{
	isFront = !isFront;
}


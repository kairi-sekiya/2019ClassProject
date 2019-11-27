#include "Card.h"
#include "Common.h"
#include <wincodec.h>
#include <d2d1.h>

Card::Card(float scale,POINT point,ID2D1Bitmap** bitmap,D2D1_SIZE_U* size)
{
	mScale = scale;
	beforeMovePoint = nowPoint = point;
	
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pFactory)
	);

	if (SUCCEEDED(hr)) {
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

}

Card::~Card()
{

}

void Card::Draw(ID2D1HwndRenderTarget* g_pRenderTarget) 
{
	ID2D1Bitmap* drawPicture;		// 描画する画像
	D2D1_SIZE_U drawPictureSize;	// 画像データの縦横の大きさ

	if (isFront) 
	{
		drawPicture = frontPicture;
		drawPictureSize = frontPictureSize;
	}
	else 
	{
		drawPicture = backPicture;
		drawPictureSize = backPictureSize;
	}

	D2D1_RECT_F drc, src;
	drc.left = 0;
	drc.top = 0;
	drc.right = drc.left + drawPictureSize.width * mScale;
	drc.bottom = drc.top + drawPictureSize.height * mScale;
	src.left = 0;
	src.top = 0;
	src.right = drawPictureSize.width * mScale;
	src.bottom = drawPictureSize.height * mScale;
	g_pRenderTarget->DrawBitmap(drawPicture, drc, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);

}

void Card::SetTargetPoint(POINT targetPoint) 
{
	this->targetPoint = targetPoint;
}

void Card::Move(float size) 
{
	
}

void Card::Warp(POINT target) {
	beforeMovePoint = nowPoint = target;
}

void Card::TurnOver() 
{
	isFront = !isFront;
}


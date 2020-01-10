#pragma once
#include <d2d1.h>
#include <wincodec.h>

class ImageLoader
{
public:
	static ImageLoader* Getinstance();
	void Release();

private:
	ImageLoader();
	static ImageLoader* instance;

public:
	ID2D1Bitmap* LoadImageFromFile(const char*& filename);

private:
	IWICImagingFactory* pFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pFormatConverter = NULL;
	WICPixelFormatGUID pixelFormat;
	D2D1_BITMAP_PROPERTIES bitmapProperties;
};


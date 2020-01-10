#pragma once
#include "include.h"

class Image
{
public:
	Image(ID2D1Bitmap* image, D2D1_SIZE_U imageSize);
	virtual ~Image();

	void Release();

	void SetImage();
	ID2D1Bitmap* GetImage();
	D2D1_SIZE_U GetImageSize();
private:
	ID2D1Bitmap** mImage;
	D2D1_SIZE_U mImageSize;
};


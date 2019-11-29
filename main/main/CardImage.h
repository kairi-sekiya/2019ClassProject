#pragma once
#include <d2d1.h>
#include <wincodec.h>

class CardImage
{
public:
	CardImage(const char* filename);
	~CardImage();

	ID2D1Bitmap* GetImage();
	D2D1_SIZE_U GetImageSize();

private:
	ID2D1Bitmap* image;
	D2D1_SIZE_U imageSize;

	void ReadImageFromFile(const char* filename);
};


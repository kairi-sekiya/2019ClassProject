#include "Image.h"
#include"include.h"

extern ID2D1HwndRenderTarget g_pRenderTarget;

Image::Image(ID2D1Bitmap* image, D2D1_SIZE_U imageSize)
{
	
}


Image::~Image()
{
}

void Image::Release() {

}

ID2D1Bitmap* Image::GetImage() {
	return mImage;
}

D2D1_SIZE_U Image::GetImageSize() {
	return mImageSize;
}



#include "ImageStorager.h"



ImageStorager::ImageStorager()
{
}


ImageStorager::~ImageStorager()
{
}

void LoadImage(const int& id,const char* filename)
{
	
}

ID2D1Bitmap* ImageStorager::GetImage(const int& id)const
{
	return imageStorage[id];
}

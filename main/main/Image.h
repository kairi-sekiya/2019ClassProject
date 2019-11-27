#pragma once
#include<d2d1.h>

class Image
{
public:
	Image();
	virtual ~Image();

public:
	ID2D1Bitmap* imageData;
	D2D1_SIZE_U imageSize;

private:

};


#pragma once
#include "ImageID.h"
struct ID2D1Bitmap;

class ImageStorager
{
public:
	static ImageStorager GetInstance();
	void Release();

private:
	ImageStorager();
	~ImageStorager();
	ImageStorager* instance;
	
	ID2D1Bitmap* imageStorage[ALL_IMAGE_COUNT];

public:
	void LoadImage(const ImageID& id);
	ID2D1Bitmap* GetImage(const int& id)const;

};


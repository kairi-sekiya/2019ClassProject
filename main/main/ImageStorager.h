#pragma once

#include"Image.h"
#include"ImageLoader.h"
#include "include.h"

#define ALL_IMAGE_COUNT 57

class ImageStorager
{
public:
	friend class ObjectFactory;
	
	static ImageStorager* instance;

private:
	static ImageStorager imageStorager;
	ImageStorager();
	~ImageStorager();

public:
	void Release();
	void LoadAllImagefromFile();

private:
	ImageLoader* imageLoader;

	// 0		カード裏
	// 1～53	カード表
	// 54		チップ
	// 55		青ボタン
	// 56		赤ボタン
	Image image[ALL_IMAGE_COUNT];

};


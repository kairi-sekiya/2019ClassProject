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

	// 0		�J�[�h��
	// 1�`53	�J�[�h�\
	// 54		�`�b�v
	// 55		�{�^��
	// 56		�ԃ{�^��
	Image image[ALL_IMAGE_COUNT];

};


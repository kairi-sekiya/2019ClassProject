#pragma once
#include "Image.h"
#include <iostream>

class ImageLoader
{
public:
	friend class ObjectFactory;

public:

	void LoadImageFromFile();
private:
	static ImageLoader instance;
	ImageLoader();
	~ImageLoader();

private:
	Image LoadImageFromFile(std::string filename);
	
};


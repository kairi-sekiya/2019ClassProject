#pragma once
#define ALL_IMAGE_COUNT 1
#define ALL_FILE_COUNT ALL_IMAGE_COUNT
#define SAFE_DELETE(o) (o->Release();o = NULL;)

class Common
{
public:
	static Common* GetInstance();
	void Release();
private:
	Common* instance;
	Common();
	
public:
	const char* Filename[ALL_FILE_COUNT];
	const int* ImageID[ALL_IMAGE_COUNT];

	
};


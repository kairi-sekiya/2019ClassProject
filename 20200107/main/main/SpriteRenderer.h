#pragma once
#include<wincodec.h>
#include<vector>
#include<d2d1.h>
#pragma comment(lib,"d2d1.lib")
#include "Sprite.h"
#include"Transform.h"
#include"ImageStorager.h"

class SpriteRenderer
{
public:
	static SpriteRenderer* GetInstance();
	void Release();

private:
	SpriteRenderer();
	SpriteRenderer* instance;

public:
	void Draw();
	int AddSprite(Sprite sprite);
	void DeleteSprite(int index);

private:
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	
	std::vector<Sprite> spriteArray;
	int spriteCount = 0;
};


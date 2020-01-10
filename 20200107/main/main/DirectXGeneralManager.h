#pragma once
#include <d2d1.h>
#pragma comment(lib,"d2d1.lib")

class DirectXGeneralManager
{
public:
	static DirectXGeneralManager* GetInstance();
	void Release();

private:
	static DirectXGeneralManager* instance;
	DirectXGeneralManager();

public:
	ID2D1HwndRenderTarget* GetRenderTarget();

private:
	ID2D1Factory* g_pD2DFactory = NULL;      //  D2D1Factoryオブジェクト
	ID2D1HwndRenderTarget* g_pRenderTarget = NULL;    //  描画ターゲット
};


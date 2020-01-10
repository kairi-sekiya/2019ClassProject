#pragma once
#include "main.h"
#include<d2d1.h>
#pragma comment(lib,"d2d1.lib")

class WindowManager
{
public:
	static WindowManager* GetInstance();
	void Release();

private:
	WindowManager();
	static WindowManager* instance;

public:
	void RegistWindowClass(HINSTANCE hInstance);
	void CreateMainWindow(HINSTANCE hInstance, int nCmdShow);
	void ResizeWindow(int width,int height);

private:


	WNDCLASSEX wcex;  //  ウィンドウクラス構造体
	HWND hWnd;        //  ウィンドウハンドル
	RECT bounds, client;  //  RECT 構造体
};


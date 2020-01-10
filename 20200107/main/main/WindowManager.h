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


	WNDCLASSEX wcex;  //  �E�B���h�E�N���X�\����
	HWND hWnd;        //  �E�B���h�E�n���h��
	RECT bounds, client;  //  RECT �\����
};


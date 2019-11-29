#pragma once

#include "Common.h"
#include<d2d1.h>
#include<wincodec.h>

class Card
{
public:
	Card(float scale,POINT point, 
		IWICImagingFactory*& pFactory,
		IWICBitmapDecoder*& pDecoder,
		IWICBitmapFrameDecode*& pFrame,
		IWICFormatConverter*& pFormatConverter,
		WICPixelFormatGUID& pixelFormat,
		HRESULT& hr,
		D2D1_BITMAP_PROPERTIES bitmapProperties,
		ID2D1HwndRenderTarget*& g_pRenderTarget
		);

	~Card();

public:
	void Draw(ID2D1HwndRenderTarget* g_pRenderTarget);
	void SetTargetPoint(POINT targetPoint);	// �ړI�n��ݒ肷��
	void Move(float size);				// targetPoint�֏����ړ�����
	void Warp(POINT target);			// 1�t���[���ň����̈ʒu�ֈړ�����
	void TurnOver();						// fromtOrBack �𗠕Ԃ�

private:
	ID2D1Bitmap* backPicture;		// �����摜�f�[�^ 
	D2D1_SIZE_U backPictureSize;	// �摜�f�[�^�̏c���̑傫��

	ID2D1Bitmap* frontPicture;		// �\���摜�f�[�^
	D2D1_SIZE_U frontPictureSize;	// �摜�f�[�^�̏c���̑傫��
	
	POINT beforeMovePoint;		// Move�ňړ�����ۂɈړ��O�̈ʒu��ۑ�
	POINT nowPoint;				// ���݂̈ʒu��ۑ�����
	POINT targetPoint;			// �ړI�n��ۑ�����

	float mScale;	// �摜�̏k�� 

	int moveTime = 0;		// �ړ��J�n����̎��ԁA�}�C�N���b�P��

	int card;				// 2���ڂ܂Ő����A3���ڂɃ}�[�N�̏��
	bool isFront = false;		// �\�� false�ŗ�

private:
};


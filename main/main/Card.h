#pragma once

#include"image.h"

class Card
{
public:
	Card(float scale,POINT point, 
		D2D1_BITMAP_PROPERTIES bitmapProperties
		);

	~Card();

public:
	void Draw(ID2D1HwndRenderTarget* g_pRenderTarget);
	void SetTargetPoint(POINT targetPoint);	// �ړI�n��ݒ肷��
	void Move(float size);				// targetPoint�֏����ړ�����
	void Warp(POINT target);			// 1�t���[���ň����̈ʒu�ֈړ�����
	void TurnOver();						// fromtOrBack �𗠕Ԃ�
	void Release();						// new�Ŋm�ۂ������������������
	void GetIsMoving();

private:
	Image* pFrontPicture;
	Image* pBackPicture;
	
	POINT beforeMovePoint;		// Move�ňړ�����ۂɈړ��O�̈ʒu��ۑ�
	POINT nowPoint;				// ���݂̈ʒu��ۑ�����
	POINT targetPoint;			// �ړI�n��ۑ�����
	double moveDistance;		// �ړ��O�ƖړI�n�̊Ԃ̋�����ۑ�

	float mScale;	// �摜�̏k�� 

	LARGE_INTEGER moveTime;		// �ړ��J�n����̎���

	int card;				// 2���ڂ܂Ő����A3���ڂɃ}�[�N�̏��
	bool isFront = false;		// �\�� false�ŗ�
	bool isMoving = false;
};


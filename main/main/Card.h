#pragma once

#include "Common.h"
#include<d2d1.h>

class Card
{
public:
	Card();
	~Card();

	void Draw(ID2D1HwndRenderTarget* g_pRenderTarget);
	void SetTargetPoint(POINT targetPoint);	// �ړI�n��ݒ肷��
	void Translate(float size);				// �ړ�������
	void TurnOver();						// fromtOrBack �𗠕Ԃ�

private:
	ID2D1Bitmap* backPicture;	// �����摜�f�[�^ 
	D2D1_SIZE_U backPictureSize;		// �摜�f�[�^�̏c���̑傫��

	ID2D1Bitmap* frontPicture;	// �\���摜�f�[�^
	D2D1_SIZE_U frontPictureSize;		// �摜�f�[�^�̏c���̑傫��
	
	POINT beforeMovePoint;		// �ړ��O�̈ʒu��ۑ�
	POINT nowPoint;				// ���݂̃J�[�h�̍���[�̈ʒu��ۑ�����
	POINT targetPoint;			// �ړI�n�̕ϐ� ���̈ʒu���ړ���ɍ���[�ɂȂ�

	float scale = DEFAULT_CARD_SIZE; // �摜�̏k��
	int moveTime = 0;		// �ړ��J�n����̎��ԁA�}�C�N���b�P��

	int card;				// 2���ڂ܂Ő����A3���ڂɃ}�[�N�̏��
	bool isFront;		// �\�� false�ŗ�
;
};


#pragma once

#include "Common.h"
#include<d2d1.h>
#include<wincodec.h>

class Card
{
public:
	Card(float scale,POINT point, 
		D2D1_BITMAP_PROPERTIES bitmapProperties
		);

	~Card();

public:
	void Draw(ID2D1HwndRenderTarget* g_pRenderTarget);
	void SetTargetPoint(POINT targetPoint);	// 目的地を設定する
	void Move(float size);				// targetPointへ少し移動する
	void Warp(POINT target);			// 1フレームで引数の位置へ移動する
	void TurnOver();						// fromtOrBack を裏返す
	void Release();						// newで確保したメモリを解放する
	void GetIsMoving();

private:
	ID2D1Bitmap* backPicture;		// 裏側画像データ 
	D2D1_SIZE_U backPictureSize;	// 画像データの縦横の大きさ

	ID2D1Bitmap* frontPicture;		// 表側画像データ
	D2D1_SIZE_U frontPictureSize;	// 画像データの縦横の大きさ
	
	POINT beforeMovePoint;		// Moveで移動する際に移動前の位置を保存
	POINT nowPoint;				// 現在の位置を保存する
	POINT targetPoint;			// 目的地を保存する
	double moveDistance;		// 移動前と目的地の間の距離を保存

	float mScale;	// 画像の縮尺 

	int moveTime = 0;		// 移動開始からの時間、マイクロ秒単位

	int card;				// 2桁目まで数字、3桁目にマークの情報
	bool isFront = false;		// 表裏 falseで裏
	bool isMoving = false;
};


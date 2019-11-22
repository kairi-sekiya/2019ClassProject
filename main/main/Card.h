#pragma once

#include "Common.h"
#include<d2d1.h>

class Card
{
public:
	Card();
	~Card();

	void Draw(ID2D1HwndRenderTarget* g_pRenderTarget);
	void SetTargetPoint(POINT targetPoint);	// 目的地を設定する
	void Translate(float size);				// 移動をする
	void TurnOver();						// fromtOrBack を裏返す

private:
	ID2D1Bitmap* backPicture;	// 裏側画像データ 
	D2D1_SIZE_U backPictureSize;		// 画像データの縦横の大きさ

	ID2D1Bitmap* frontPicture;	// 表側画像データ
	D2D1_SIZE_U frontPictureSize;		// 画像データの縦横の大きさ
	
	POINT beforeMovePoint;		// 移動前の位置を保存
	POINT nowPoint;				// 現在のカードの左上端の位置を保存する
	POINT targetPoint;			// 目的地の変数 この位置が移動後に左上端になる

	float scale = DEFAULT_CARD_SIZE; // 画像の縮尺
	int moveTime = 0;		// 移動開始からの時間、マイクロ秒単位

	int card;				// 2桁目まで数字、3桁目にマークの情報
	bool isFront;		// 表裏 falseで裏
;
};


#pragma once
#include "Vector2.h"


// Vector3を実装してtransformを全てVector3で扱うようにする
class Transform
{
public:
	Transform(const Vector2& position, const Vector2& rotation, const Vector2& scale);
	~Transform();

	Vector2 position;
	Vector2 rotation;
	Vector2 scale;

	// 以下関数定義
	template <typename NUM>
	void Position(NUM x,NUM y);
	template <typename NUM>
	void Translate(NUM x, NUM y);
	template <typename NUM>
	void Rotate(NUM x, NUM y);
	template <typename NUM>
	void Scale(NUM x, NUM y);
};


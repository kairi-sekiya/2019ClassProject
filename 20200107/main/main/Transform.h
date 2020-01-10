#pragma once
#include "Vector2.h"


// Vector3‚ğÀ‘•‚µ‚Ätransform‚ğ‘S‚ÄVector3‚Åˆµ‚¤‚æ‚¤‚É‚·‚é
class Transform
{
public:
	Transform(const Vector2& position, const Vector2& rotation, const Vector2& scale);
	~Transform();

	Vector2 position;
	Vector2 rotation;
	Vector2 scale;

	// ˆÈ‰ºŠÖ”’è‹`
	template <typename NUM>
	void Position(NUM x,NUM y);
	template <typename NUM>
	void Translate(NUM x, NUM y);
	template <typename NUM>
	void Rotate(NUM x, NUM y);
	template <typename NUM>
	void Scale(NUM x, NUM y);
};


#pragma once
#include "Common.h"
#include "Transform.h"
struct Sprite
{
	Sprite(int id, Transform transform)
		:id(&id), transform(&transform) {};

	int* id;
	Transform* transform;
	
	Sprite& operator=(const Sprite& other);
};


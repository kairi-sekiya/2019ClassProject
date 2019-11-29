#pragma once
#include <d2d1.h>

class Time
{
public:
	Time();

	inline LARGE_INTEGER GetDeltaTime();
	void UpdateParameters();
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER deltaTime;
	LARGE_INTEGER nowTime;
	LARGE_INTEGER oldTime;
};


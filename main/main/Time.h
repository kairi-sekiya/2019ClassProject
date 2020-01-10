#pragma once
#include"include.h"

class Time
{
public:
	Time();

	LARGE_INTEGER GetDeltaTime();
	void UpdateParameters();
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER deltaTime;
	LARGE_INTEGER nowTime;
	LARGE_INTEGER oldTime;
};


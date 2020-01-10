#include "Time.h"



Time::Time()
{
	memset(&deltaTime,	0x00, sizeof deltaTime);
	memset(&oldTime,	0x00, sizeof oldTime);
	memset(&nowTime,	0x00, sizeof nowTime);
	memset(&frequency,	0x00, sizeof frequency);
}


void Time::UpdateParameters() 
{	
	QueryPerformanceCounter(&nowTime);
	QueryPerformanceFrequency(&frequency);
	deltaTime.QuadPart = ((nowTime.QuadPart - oldTime.QuadPart) * 1000 / frequency.QuadPart);
	oldTime = nowTime;
}

LARGE_INTEGER Time::GetDeltaTime() {
	return deltaTime;
}
#include "Headers/pch.h"
#include "Headers/timer.h"

#ifdef WINDOWS_TIMER

windowsTimer::windowsTimer()
	: start(0), end(0), delta(0), freq(0), mSecPerCount(0)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&start);
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	mSecPerCount = 1.0 / (double)freq;
}

windowsTimer::~windowsTimer()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&end);

	delta = end - start;
}

void windowsTimer::Tick()
{
	INT64 curTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

	delta = (curTime - start)*mSecPerCount;
}

//same as curr time just gets the delta
double windowsTimer::CurrTime() const 
{
	return delta;
}

#endif


#ifndef WINDOWS_TIMER

Timer::Timer()
	:currTime(0), dur(0)
{
	start = clock.now();
}

Timer::~Timer()
{
	end = clock.now();
}

double Timer::CurrTime() const
{
	return currTime;
}

void Timer::Tick()
{
	cur = clock.now();
	dur = cur - start;

	currTime = dur.count();
}

#endif
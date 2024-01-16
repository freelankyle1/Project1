#pragma once
#include "../pch.h"

//#define WINDOWS_TIMER 

#ifdef WINDOWS_TIMER

class windowsTimer
{
public:
	windowsTimer();
	~windowsTimer();

	void Tick();
	double CurrTime() const;

private:
	INT64 start, end, delta;
	INT64 freq;

	double mSecPerCount;

};

#endif


#ifndef WINDOWS_TIMER

class Timer
{
public:
	Timer(); //starts the timer;
	~Timer(); //ends the timer;

	void Tick();

	double CurrTime() const;

private:
	std::chrono::high_resolution_clock clock;
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end, cur;
	std::chrono::duration<float> dur;
	double currTime;
};

#endif

#include "Headers/pch.h"
#include "Headers/gametimer.h"

gameTimer::gameTimer()
	:mSecondsPerCount(0), mDeltaTime(-1), mBaseTime(0), 
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(FALSE), mStopTime(0)
{
	INT64 countsPerSec;

	QueryPerformanceCounter((LARGE_INTEGER*)&countsPerSec);

	mSecondsPerCount = 1.0 / (DOUBLE)countsPerSec;

}

void gameTimer::tick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	//gets the time on the current frame
	INT64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	//time difference between the current and the previous frame
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
		mDeltaTime = 0.0;
}

FLOAT gameTimer::deltaTime() CONST
{
	return (FLOAT)mDeltaTime;
}

void gameTimer::reset()
{
	INT64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void gameTimer::stop()
{
	if (!mStopped)
	{
		INT64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		mStopTime = currTime;
		mStopped = true;
	}
}

void gameTimer::start()
{
	INT64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	if (mStopped)
	{
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;

		mStopTime = 0;
		mStopped = false;
	}
}

FLOAT gameTimer::totalTime() CONST
{
	if (mStopped)
	{
		return (FLOAT)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
	else
	{
		return (FLOAT)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
}
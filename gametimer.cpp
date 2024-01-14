#include "pch.h"
#include "Headers/gametimer.h"

gameTimer::gameTimer()
	:mSecondsPerCount(0), mDeltaTime(-1), mBaseTime(0), 
	mPausedTime(0), mPrevTime(0), mCurrTime(0), mStopped(FALSE)
{
	INT64 countsPerSec;

	QueryPerformanceCounter((LARGE_INTEGER*)&countsPerSec);

	mSecondsPerCount = 1.0 / (DOUBLE)countsPerSec;

}


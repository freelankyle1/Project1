#pragma once
#include "pch.h"


class gameTimer
{
public:

	gameTimer();

	FLOAT gameTime();
	FLOAT deltaTime() CONST;
	FLOAT totalTime() CONST;


	void reset();
	void start();
	void stop();
	void tick();

private:
	DOUBLE mSecondsPerCount;
	DOUBLE mDeltaTime;

	INT64 mBaseTime;
	INT64 mPausedTime;
	INT64 mStopTime;
	INT64 mPrevTime;
	INT64 mCurrTime;

	BOOL mStopped;
};
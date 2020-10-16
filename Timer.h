#pragma once
#ifndef aTimerFile
#define aTimerFile

#include <iostream>
#include <SDL.h>

class Timer
{
private:
	int startTicks;

public:
	Timer();

	void resetTicksTimer();
	int getTicks();

};

#endif
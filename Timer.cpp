#include "Timer.h"

Timer::Timer()
{
	startTicks = 0;
};

void Timer::resetTicksTimer()
{
	startTicks = SDL_GetTicks();
	//printf("Timer has started");
}

int Timer::getTicks()
{
	return (SDL_GetTicks() - startTicks);
}
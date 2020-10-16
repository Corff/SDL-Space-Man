#include "Clock.h"


pClock::pClock()
{
	font = TTF_OpenFont("content/GameOver/Pixeled.ttf", 100);
	Color = { 0,0,255,255 };
	
	surfaceText = TTF_RenderText_Solid(font, cArray, Color);
	text = SDL_CreateTextureFromSurface(r, surfaceText);
	messageRect = { 100,0,50,75 };

	SDL_FreeSurface(surfaceText);
}

void pClock::tick()
{
	if(iter == 100)
	{
		seconds++;
		message = std::to_string(seconds);
		int n = message.length();
		strcpy_s(cArray, message.c_str());
		iter = 0;
	}
	iter++;
}


void pClock::Render(SDL_Renderer* r)
{
	surfaceText = TTF_RenderText_Solid(font, cArray, Color);
	text = SDL_CreateTextureFromSurface(r, surfaceText);
	SDL_FreeSurface(surfaceText);
	SDL_RenderCopy(r, text, NULL, &messageRect);
}

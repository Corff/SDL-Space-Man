#pragma once

#include <iostream>
#include "SDL.h"
#include <SDL_ttf.h>
#include "SDL_image.h"
#include<string>

class pClock
{

public:
	pClock();
	~pClock();


	void Render(SDL_Renderer* r);
	void collision();
	void tick();
	std::string message;
	char cArray[99];
	int seconds;
	int iter = 0;
	SDL_Renderer* r;
	TTF_Font* font;
	SDL_Color Color;
	SDL_Surface* surfaceText;
	SDL_Texture* text;
	SDL_Rect messageRect;


};
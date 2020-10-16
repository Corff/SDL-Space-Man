#pragma once

#include <iostream>
#include <SDL_ttf.h>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include <math.h>

class Health
{
public:
	Health(SDL_Renderer* r);
	~Health();

	void Init();
	void Update();
	void Render();

	const float healthNumStart = 1000.0f;
	float healthNum;
	char cArray[99];
	
	SDL_Renderer* re;

	SDL_Surface* surface;
	SDL_Texture* tex;
	SDL_Rect messageRect;
	TTF_Font* font;
	SDL_Color Color;
};

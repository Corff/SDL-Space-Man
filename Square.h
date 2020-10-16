#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class Square
{

public:
	Square();
	~Square();

	void Init();

	void Render(SDL_Renderer* r);
	void collision();

	SDL_Rect rect;

	
};
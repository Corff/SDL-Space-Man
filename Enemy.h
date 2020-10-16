#pragma once
#ifndef aEnemyFile
#define aEnemyFile


#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

class enemy
{
public:
	enemy(SDL_Renderer* r);
	~enemy();

	void Init();
	void Update(SDL_Rect playerRect);
	void Input(SDL_Event e);
	void Render();
	void Animate();
	bool collision();
	
	int X, Y, Height, Width, r, g, b, xFrameIndex, yFrameIndex, enemySize, speed;
	bool up, down, left, right, shoot, shootUp, shootDown, idle;

	SDL_Renderer* re;

	int sheet[99][99] = { {0,0}, {0,1}, {0,2}, {1,0} };
	
	SDL_Surface* surface;
	SDL_Texture* tex;
	SDL_RendererFlip f;
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	
};



#endif

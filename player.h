#pragma once
#ifndef aPlayerFile
#define aPlayerFile

#include <iostream>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "bullet.h"
#include <vector>

class player
{
public:
	player(SDL_Renderer* r);
	~player();

	void Init();
	void Update();
	void Input(SDL_Event e);
	void Render();
	void animate();
	bool collision(SDL_Rect r1,SDL_Rect r2);
	void shoot();
	
	int X, Y, Height, Width, r, g, b, xFrameIndex, yFrameIndex , playerSize, imgWidth,imgHeight;
	bool up, down, left, right, idle, shooting;

	//std::vector<bullet*> bullets;
	
	SDL_Renderer* re;

	SDL_Event ev;
	
	SDL_Surface* surface;
	SDL_Texture* tex;
	SDL_RendererFlip f;
	SDL_Rect srcRect;
	SDL_Rect dstRect ;

};
#endif
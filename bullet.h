#pragma once
#include <SDL.h>
#include <SDL_Image.h>
#include <cstdio>
#include "SDL_mixer.h"

class bullet
{	
public:

	bullet(SDL_Renderer* r, int sp);
	~bullet();

	void fire(SDL_Event e, int playerXi, int playerYi);

	void Update(int playerXi, int playerYi);

	void Render();

	bool collision(SDL_Rect r1, SDL_Rect r2);

	bool active = false;
	int speed,targetX,targetY,playerX,playerY;
	
	SDL_Surface* surface;
	SDL_Texture* tex;
	SDL_Renderer* re;
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	//Sound
	Mix_Chunk* gunshot;
	
};

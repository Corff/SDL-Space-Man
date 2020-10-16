#include "bullet.h"

#include <iostream>

bullet::bullet(SDL_Renderer* r, int sp)
{
	speed = sp;
	re = r;
	surface = IMG_Load("content/Bullet/Bullet2.png");
	tex = SDL_CreateTextureFromSurface(re, surface);
	SDL_FreeSurface(surface);


	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 32;
	srcRect.h = 32;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = 32;
	dstRect.h = 32;

	gunshot = Mix_LoadWAV("content/sound/laser.wav");
	Mix_VolumeChunk(gunshot, 16);
}

bullet::~bullet()
{
	
}

void bullet::fire(SDL_Event e, int playerXi, int playerYi)
{
	if(!active)
	{
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&targetX, &targetY);
			active = true;
			playerX = playerXi;
			playerY = playerYi;
			dstRect.x = playerX + 75/2;
			dstRect.y = playerY + 75/2;
			Mix_PlayChannel(-1,gunshot,0);
		}
	}
}

void bullet::Update(int playerXi,int playerYi)
{

	if(!active)
	{
		dstRect.x = 999999999;
		dstRect.y = 999999999;
	}
	if(active)
	{


		if(targetX > playerX)//Right
		{
			if (targetY > playerY && targetY < playerY + 75)
			{
				dstRect.x = dstRect.x + (20*speed);
			}
			else if (targetY > playerY)
			{
				dstRect.x = dstRect.x + (10 * speed);
				dstRect.y = dstRect.y + (10 * speed);
			}
			else if(targetY < playerY)
			{
				dstRect.x = dstRect.x + (10 * speed);
				dstRect.y = dstRect.y - (10 * speed);
			}

		}
		else if(targetX < playerX)//Left
		{
			if (targetY > playerY && targetY < playerY + 75)
			{
				dstRect.x = dstRect.x - (20 * speed);
			}
			else if (targetY > playerY)
			{
				dstRect.x = dstRect.x - (10 * speed);
				dstRect.y = dstRect.y + (10 * speed);
			}
			else if (targetY < playerY)
			{
				dstRect.x = dstRect.x - (10 * speed);
				dstRect.y = dstRect.y - (10 * speed);
			}
		}
		else
		{
			printf("BROKE");
			std::cout << "X: " << targetX << std::endl << "Y: " << targetY << std::endl;
		}
	}

	if(dstRect.x >= 800 || dstRect.x <= 0)
	{
		active = false;
	}
	if(dstRect.y >=600 || dstRect.y <= 0)
	{
		active = false;
	}
	
}

void bullet::Render()
{
	SDL_RenderCopy(re,tex,&srcRect,&dstRect);
}

bool bullet::collision(SDL_Rect r1, SDL_Rect r2)
{
	// Find edges of srcRect1
	int left1 = r1.x;
	int right1 = r1.x + r1.w;
	int top1 = r1.y;
	int bottom1 = r1.y + r1.h;

	// Find edges of srcRect2
	int left2 = r2.x;
	int right2 = r2.x + r2.w;
	int top2 = r2.y;
	int bottom2 = r2.y + r2.h;


	if (left1 > right2)// Left 1 is right of right 2
		return false; // No collision

	if (right1 < left2) // Right 1 is left of left 2
		return false; // No collision

	if (top1 > bottom2) // Top 1 is below bottom 2
		return false; // No collision

	if (bottom1 < top2) // Bottom 1 is above top 2
		return false; // No collision

	return true;
}
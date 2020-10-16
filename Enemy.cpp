#include "Enemy.h"

enemy::enemy(SDL_Renderer* r)
{
	re = r;
	SDL_Log("Enemy Constructed");
	Init();
}

enemy::~enemy()
{
	SDL_Log("Enemy Destructed");
}

void enemy::Init()
{
	surface = IMG_Load("content/Alien/alien.png");
	tex = SDL_CreateTextureFromSurface(re, surface);
	SDL_FreeSurface(surface);

	xFrameIndex = 0;
	yFrameIndex = 0;

	enemySize = 50;
	
	srcRect.x = 27 * xFrameIndex;
	srcRect.y = 53 * yFrameIndex;
	srcRect.w = 27;
	srcRect.h = 53;
	
	dstRect.x = 500;
	dstRect.y = 500;
	dstRect.h = enemySize+25;
	dstRect.w = enemySize;

	up = false;
	down = false;
	left = false;
	right = false;
	
}

void enemy::Update(SDL_Rect playerRect)
{

	if(dstRect.x < playerRect.x)
	{
		dstRect.x = dstRect.x + speed;
	}
	if(dstRect.y < playerRect.y)
	{
		dstRect.y = dstRect.y + speed;
	}
	
	if (dstRect.x > playerRect.x)
	{
		dstRect.x = dstRect.x - speed;
	}
	if (dstRect.y > playerRect.y)
	{
		dstRect.y = dstRect.y - speed;
	}

	Animate();
	
}


void enemy::Render()
{
	SDL_RenderCopy(re, tex, &srcRect, &dstRect);
}

void enemy::Animate()
{
	//int sheet[99] = { {0,0}, {0,1}, {0,2}, {1,0} };

	unsigned int ticks = SDL_GetTicks();
	unsigned int changeTimeMS = 200;
	int changer = (ticks / changeTimeMS) % 4;

	xFrameIndex = sheet[changer][0];
	yFrameIndex = sheet[changer][1];
	
}

bool enemy::collision()
{

	return false;
	
}



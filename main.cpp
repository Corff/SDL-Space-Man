#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <time.h>
#include "Timer.h"
#include <SDL_ttf.h>
#include "Clock.h"
#include "Enemy.h"
#include "player.h"
#include <vector>
#include <ctime>
#include "health.h"
#include <fstream>

using namespace std;

bool getTime(char* buffer, int buffersize);
void logData(void* userdata, int category, SDL_LogPriority priority, const char* message);
std::ofstream logFile;

int main(int argc, char* argv[])
{
	//Initialising
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		return false;
	}
	if (TTF_Init() == -1)
	{
		return false;
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	//Window and Renderer
	Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	SDL_Window* window = SDL_CreateWindow("Tom Jackson 16652901", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
	int full = 0;
	SDL_Renderer* r = SDL_CreateRenderer(window, 0, 0);

	//Timer
	Timer t;
	bool running = true;
	const int DELTA_TIME = 10;

	//Clock
	pClock* clock = new pClock;

	//Player
	player* p = new player(r);

	//Health
	Health* h = new Health(r);

	//Sound
	Mix_Chunk* hitsound = Mix_LoadWAV("content/Sound/hitsound.wav");
	int v = 1;
	Mix_VolumeChunk(hitsound, 32);

	//Enemy
	vector<enemy*> enemies;
	srand(time(0));

	//Bullets
	bullet* b = new bullet(r,1);
	bullet* b2 = new bullet(r,3);
	int bulletSize = 20;
	b2->dstRect.w = bulletSize;
	b2->dstRect.h = bulletSize;
	bool oneOrTwo = true;

	//Moon
	SDL_Surface* moonSurface = IMG_Load("content/Moon/Moon.png");
	SDL_Texture* moonTex = SDL_CreateTextureFromSurface(r, moonSurface);
	SDL_Rect dstRectMoon = { 0,0,800,600 };

	//GameOver
	TTF_Font* font = TTF_OpenFont("content/GameOver/Pixeled.ttf", 100);
	SDL_Color color = { 255,0,0,255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", color);
	SDL_Texture* texe = SDL_CreateTextureFromSurface(r, surface);
	SDL_Rect mRect = { 350,250,100,100 };

	//Event-
	SDL_Event e;

	//Logging
	logFile.open("game-log.txt");
	if (!logFile.is_open())
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open file");
	SDL_LogSetOutputFunction(&logData, NULL);

	int x, y;
	bool paused = false;

	//Splash Screen
	SDL_Surface* splashSurface = IMG_Load("content/Splash/Splash.png");
	SDL_Texture* splashTexture = SDL_CreateTextureFromSurface(r, splashSurface);
	SDL_Rect dstRectSplash = { 0, 0, 800, 600 };
	SDL_RenderCopy(r, splashTexture, NULL, &dstRectSplash);
	SDL_RenderPresent(r);
	SDL_Delay(2000);


	//InventoryIcons
	SDL_Surface* icon1Surface = IMG_Load("content/Icons/Size.png");
	SDL_Surface* icon2Surface = IMG_Load("content/Icons/Speed.png");
	SDL_Texture* icon1Tex = SDL_CreateTextureFromSurface(r,icon1Surface);
	SDL_Texture* icon2Tex = SDL_CreateTextureFromSurface(r,icon2Surface);
	SDL_Rect icon1Rect = {345,550,50,50};
	SDL_Rect icon2Rect = {405,550,50,50};
	
	
	//Game Loop
	while (running)
	{
		if (h->healthNum > 0 && !paused)
		{
			t.resetTicksTimer();
			while (SDL_PollEvent(&e))
			{
				p->Input(e);
				if(oneOrTwo)
					b->fire(e, p->dstRect.x, p->dstRect.y);
				if (!oneOrTwo)
					b2->fire(e, p->dstRect.x, p->dstRect.y);
				if(e.type == SDL_KEYDOWN && e.key.repeat == NULL)
				{
					if(e.key.keysym.sym == SDLK_m)
					{
						if(v == 1)
						{
							Mix_Volume(-1, 0);
							SDL_Log("Muted");
							v = 0;
						}
						else if(v == 0)
						{
							SDL_Log("Unmuted");
							Mix_Volume(-1, 128);
							v = 1;
						}
					}
					if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						paused = true;
					}
					if(e.key.keysym.sym == SDLK_RETURN)
					{
						if(full == 0)
						{
							SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
							full = 1;
						}
						else if (full == 1)
						{
							SDL_SetWindowFullscreen(window, SDL_WINDOW_BORDERLESS);
							full = 0;
						}
						
					}
					if(e.key.keysym.sym == SDLK_1)
					{
						oneOrTwo = true;
					}
					if (e.key.keysym.sym == SDLK_2)
					{
						oneOrTwo = false;
					}
				}


				//Logging
				SDL_Keycode keyPressed = e.key.keysym.sym;
				char timestr[32];
				getTime(timestr, 32);
				if (e.type == SDL_KEYDOWN && !e.key.repeat)
					SDL_Log("[%s] [KeyDown] time %d; code %d; char %s;", timestr, e.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
				else if(e.type == SDL_KEYUP)
					SDL_Log("[%s] [KeyUp] time %d; code %d; char %s;", timestr, e.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
				else if(e.type == SDL_MOUSEBUTTONDOWN)
					SDL_Log("[%s] [MouseDown] time %d; code %d; char %s;", timestr, e.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
				else if(e.type == SDL_MOUSEBUTTONUP)
					SDL_Log("[%s] [MouseUp] time %d; code %d; char %s;", timestr, e.key.timestamp, keyPressed, SDL_GetKeyName(keyPressed));
			}
			SDL_GetMouseState(&x, &y);
			int xi = p->dstRect.x + ((p->playerSize + 20) / 2);
			int yi = p->dstRect.y + (p->playerSize / 2);
			if(oneOrTwo)
				b->Update(xi, yi);
			if (!oneOrTwo)
				b2->Update(xi, yi);
			p->Update();

			//Render BackGround
			SDL_RenderCopy(r,moonTex,NULL,&dstRectMoon);

			//Health
			h->Update();
			h->Render();

			//Render Bullets
			if(oneOrTwo)
				b->Render();
			if (!oneOrTwo)
				b2->Render();

			//Render Player
			p->Render();

			//Render Clock
			clock->tick();
			clock->Render(r);

			//Render Enemies
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i]->Update(p->dstRect);
				enemies[i]->Render();
			}

			//Icons
			if(oneOrTwo)
			{
				icon1Rect = {320,525,75,75};
				icon2Rect = { 405,550,50,50 };
			}
			if(!oneOrTwo)
			{
				icon1Rect = { 345,550,50,50 };
				icon2Rect = { 405,525,75,75 };
			}
			SDL_RenderCopy(r, icon1Tex, NULL, &icon1Rect);
			SDL_RenderCopy(r, icon2Tex, NULL, &icon2Rect);
			
			//Enemy collision with bullets
			for (int i = 0; i < enemies.size(); i++)
			{
				if(oneOrTwo)
				{
					if (b->collision(b->dstRect, enemies[i]->dstRect))
					{
						delete enemies[i];
						enemies.erase(enemies.begin() + i);
						Mix_PlayChannel(-1, hitsound, 0);
					}
				}
				if(!oneOrTwo)
				{
					if (b2->collision(b2->dstRect, enemies[i]->dstRect))
					{
						delete enemies[i];
						enemies.erase(enemies.begin() + i);
						Mix_PlayChannel(-1, hitsound, 0);
					}
				}


			}

			//Enemy collision with player
			for (int i = 0; i < enemies.size(); i++)
			{

				if (p->collision(p->dstRect, enemies[i]->dstRect))
				{

					h->healthNum = h->healthNum - 1;
					//cout << h->healthNum << endl;
					
				}

			}

			//Refill Enemies
			if (enemies.size() == 0)
			{
				for (int i = 0; i < 5; i++)
				{
					enemy* e = new enemy(r);
					e->dstRect.x = rand() % 800;
					e->dstRect.y = rand() % 600;
					e->speed = rand() % 2 + 1;
					enemies.push_back(e);
				}
			}

			SDL_RenderPresent(r);
			//SDL_Delay(5000);
			if (t.getTicks() < DELTA_TIME)
			{
				SDL_Delay(DELTA_TIME - t.getTicks());

			}
		}
		if(paused)
		{
			t.resetTicksTimer();

			while(SDL_PollEvent(&e))
			{
				if (e.type == SDL_KEYDOWN && e.key.repeat == NULL)
				{
					if(e.key.keysym.sym == SDLK_ESCAPE)
					{
						paused = false;
					}
				}
			}
			
			if (t.getTicks() < DELTA_TIME)
			{
				SDL_Delay(DELTA_TIME - t.getTicks());

			}
		}
		if(h->healthNum <= 0)
		{
			int i = 0;
			if(i==0)
			{
				SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
				SDL_RenderClear(r);
				SDL_RenderCopy(r, texe, NULL, &mRect);

				SDL_RenderPresent(r);
				i = 1;
			}

		}
		
	}
	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
	
}

bool getTime(char* buffer, int buffersize)
{
	time_t currentTime = std::time(0);

	struct tm info;
	localtime_s(&info, &currentTime);

	size_t written = strftime(buffer, buffersize, "%d/%m/%y", &info);

	return written != 0;
}

void logData(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	cout << message << endl;

	logFile << message << endl;
}

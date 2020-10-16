#include "health.h"
Health::Health(SDL_Renderer* r)
{
	re = r;
	font = TTF_OpenFont("content/GameOver/Pixeled.ttf", 100);
	Color = { 255,0,0,255 };
	healthNum = healthNumStart;
	surface = TTF_RenderText_Solid(font, cArray, Color);
	tex = SDL_CreateTextureFromSurface(re, surface);
	messageRect = { 600,0,100,75 };
	SDL_FreeSurface(surface);
}
void Health::Update()
{
	float perc = (healthNum / healthNumStart) * 100;
	int dperc = roundf(perc * 100) / 100;
	std::string cstring = "Health: " + std::to_string(dperc);
	strcpy_s(cArray, cstring.c_str());
}
void Health::Render()
{
	surface = TTF_RenderText_Solid(font, cArray, Color);
	tex = SDL_CreateTextureFromSurface(re, surface);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(re, tex, NULL, &messageRect);
}
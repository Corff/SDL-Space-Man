#include "Square.h"

Square::Square()
{
	rect = {0,0,0,0};
}

Square::~Square()
{
	
}

void Square::Init()
{
	
}

void Square::Render(SDL_Renderer* r)
{

	SDL_RenderFillRect(r, &rect);
	
}

void Square::collision()
{
	
}

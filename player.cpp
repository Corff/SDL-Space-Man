#include "player.h"

player::player(SDL_Renderer* r)
{
    re = r;
    SDL_Log("Player Constructed");
    Init();
}
player::~player()
{
    SDL_Log("Player Destructed");
}

void player::Init()
{
    surface = IMG_Load("content/Spaceman/MrSpaceman.png");
    tex = SDL_CreateTextureFromSurface(re, surface);
    SDL_FreeSurface(surface);
	
    xFrameIndex = 0;
    yFrameIndex = 0;

    playerSize = 75;

    imgWidth = 79;
    imgHeight = 49;
	
    srcRect.x = imgWidth * xFrameIndex;
    srcRect.y = imgHeight * yFrameIndex;
    srcRect.w = imgWidth;
    srcRect.h = imgHeight;

    dstRect.x = 0;
    dstRect.y = 0;
    dstRect.h = playerSize;
	dstRect.w = playerSize+20;

    up = false;
    down = false;
    left = false;
    right = false;
	
}

void player::Update()
{
    idle = true;
    int speed = 3;
    if (up && dstRect.y < 600-playerSize)
    {
        dstRect.y += speed;
        //SDL_Log("Moving Down");
    }
    if (left && dstRect.x > 0)
    {
        dstRect.x -= speed;
        //SDL_Log("Moving Left");
    }
    if (down && dstRect.y > 0)
    {
        dstRect.y -= speed;
        //SDL_Log("Moving Up");
    }
    if (right && dstRect.x < 800 - playerSize)
    {
        dstRect.x += speed;
        //SDL_Log("Moving Right");
    }
	
    int x,y;
    SDL_GetMouseState(&x, &y);

	if(x < dstRect.x + ((playerSize+20)/2))
	{
        f = SDL_FLIP_HORIZONTAL;
	}
    else
    {
        f = SDL_FLIP_NONE;
    }

    animate();

    srcRect.x = imgWidth * xFrameIndex;
    srcRect.y = imgHeight * yFrameIndex;

    
	
}

void player::Input(SDL_Event e)
{
    ev = e;
    if (e.type == SDL_KEYDOWN && e.key.repeat == NULL)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_SPACE:
            //increment = 0;
            //printf("space pressed \n");
            break;
        case SDLK_w:
            //increment = 5;
            down = true;
            //printf("w down \n");
            break;
        case SDLK_a:
            //increment = 5;
            left = true;
            //printf("a down \n");
            break;
        case SDLK_s:
            //increment = 5;
            up = true;
            //printf("s down \n");
            break;
        case SDLK_d:
            //increment = 5;
            right = true;
            //printf("d down \n");
            break;
        }
    }
    if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_w:
            down = false;
            //SDL_Log("Up Released");
            break;
        case SDLK_a:
            left = false;
            //SDL_Log("Right Released");
            break;
        case SDLK_s:
            up = false;
            //SDL_Log("Down Released");
            break;
        case SDLK_d:
            right = false;
            //SDL_Log("Right Released");
            break;
        }
    }
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
        shooting = true;
        idle = false;
	}
}

void player::Render()
{
    SDL_RenderCopyEx(re,tex,&srcRect,&dstRect,NULL,NULL, f);
}

void player::animate()
{
    int y;
    SDL_GetMouseState(NULL, &y);
    if(y > dstRect.y + imgHeight)//Down
    {
        yFrameIndex = 2;
    	if(ev.type == SDL_MOUSEBUTTONDOWN)
    	{
            xFrameIndex = 1;
    	}
        else
        {
            xFrameIndex = 0;
        }
    }
	if(y < dstRect.y)//Up
	{
        yFrameIndex = 1;
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            xFrameIndex = 1;
        }
        else
        {
            xFrameIndex = 0;
        }
	}
	if(y>dstRect.y && y<dstRect.y+imgHeight)//Mid
	{
        yFrameIndex = 0;
        if (ev.type == SDL_MOUSEBUTTONDOWN)
        {
            xFrameIndex = 1;
        }
        else
        {
            xFrameIndex = 0;
        }
	}
}

bool player::collision(SDL_Rect r1,SDL_Rect r2)
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

    //std::cout << " COLLISION " << std::endl;
    return true;
}
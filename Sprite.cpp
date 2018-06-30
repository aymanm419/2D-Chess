#include "Sprite.h"
#include <vector>
#include <iostream>
#include <cmath>
#define epison 1e-4
#define MATH_PI 3.1415926535897932384626433832795
Sprite::Sprite(SDL_Renderer* renderer,char* FileDir,int x,int y,int w,int h)
{
    curTexture = IMG_LoadTexture(renderer,FileDir);
    SDL_QueryTexture(curTexture,NULL,NULL,&img_width,&img_height);
    mainRect.x = x;
    mainRect.y = y;
    mainRect.w = w;
    mainRect.h = h;
    timeSinceLastMove = 0;
    cropRect.x = -1;
}
Sprite::~Sprite()
{
    SDL_DestroyTexture(curTexture);
}
void Sprite::SetX(int value)
{
    mainRect.x = value;
}
void Sprite::SetY(int value)
{
    mainRect.y = value;
}
void Sprite::setCropDetails(int cropX,int cropY,int cropW,int cropH)
{
    cropRect.x = cropX;
    cropRect.y = cropY;
    cropRect.w = cropW;
    cropRect.h = cropH;
}
void Sprite::setRectDetails(int x,int y,int w,int h)
{
    mainRect.x = x;
    mainRect.y = y;
    mainRect.w = w;
    mainRect.h = h;
}



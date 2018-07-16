#include "Sprite.h"
#include <vector>
#include <iostream>
#include <cmath>
Sprite::Sprite(SDL_Renderer* renderer,char* FileDir,int x,int y,int w,int h)
{
    curTexture = IMG_LoadTexture(renderer,FileDir);
    SDL_QueryTexture(curTexture,NULL,NULL,&img_width,&img_height);
    setRectDetails(x,y,w,h);
    cropRect.x = -1;
}
Sprite::Sprite(const Sprite& sp)
{
    curTexture = sp.getTexture();
    img_width = sp.img_width;
    img_height = sp.img_height;
    setRectDetails(sp.mainRect.x,sp.mainRect.y,sp.mainRect.w,sp.mainRect.h);
    setCropDetails(sp.cropRect.x,sp.cropRect.y,sp.cropRect.w,sp.cropRect.h);
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
void Sprite::setPosition(int X,int Y)
{
    mainRect.x = X;
    mainRect.y = Y;
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




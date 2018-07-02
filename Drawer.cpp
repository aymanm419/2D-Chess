#include "Drawer.h"
#include <iostream>
void Drawer::Draw(Sprite* curSprite,Init& CurGame)
{
    SDL_Rect CropRect = curSprite->getCropRect();
    SDL_Rect MainRect = curSprite->getMainRect();
    if(CropRect.x != -1)
        SDL_RenderCopy(CurGame.renderer,curSprite->getTexture(),&CropRect,&MainRect);
    else
        SDL_RenderCopy(CurGame.renderer,curSprite->getTexture(),NULL,&MainRect);
}

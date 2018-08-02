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
void Drawer::DrawPieces(std::vector<Piece*>& VectorSprite,Init& curGame)
{
    for(std::vector<Piece*>::iterator it = VectorSprite.begin();it != VectorSprite.end();it++)
    {
        if(!(*it)->isDead)
             Draw((*it)->PieceImg,curGame);
    }
}
void Drawer::DrawSprites(std::vector<Sprite*>& VectorSprite,Init& curGame)
{
    for(std::vector<Sprite*>::iterator it = VectorSprite.begin();it != VectorSprite.end();it++)
        Draw(*it,curGame);
}

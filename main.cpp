#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Sprite.h"
#include "Init.h"
#include "Drawer.h"
#include <vector>
#include "GameController.h"
char* backgroundImg = "chessBack.bmp";
Sprite* curBoard;
Sprite* SpriteTile;
Piece* TemporaryChoosen;
int main( int argc, char * argv[] )
{
    Drawer GameDrawer;
    Init Game;
    GameController GameHandler;
    curBoard = new Sprite(Game.renderer,backgroundImg,0,0,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT);
    SpriteTile = new Sprite(Game.renderer,"ChoosenSprite.png",0,0,64,64);
    Game.InitializeBlack();
    Game.InitializeWhite();
    while(!Game.quit && Game.mainEvent->type != SDL_QUIT)
    {
        Game.Begin();
        GameDrawer.Draw(curBoard,Game);
        if(GameHandler.lastChoosenPiece != NULL)
        {
            SpriteTile->setPosition(GameHandler.lastChoosenPiece->getImg()->getX(),GameHandler.lastChoosenPiece->getImg()->getY());
            GameDrawer.Draw(SpriteTile,Game);
        }
        if(GameHandler.TileEffects.size() > 0)
            GameDrawer.DrawSprites(GameHandler.TileEffects,Game);
        GameDrawer.DrawPieces(Game.getPieces(),Game);
        if(GameHandler.isMouseDown(Game))
        {
            SDL_GetMouseState(&Game.mouseX,&Game.mouseY);
            if(GameHandler.isValidClick(Game))
            {
                GameHandler.initalizeClick(Game);
                TemporaryChoosen = GameHandler.getPieceInRectangle(Game.getPieces(),Game.mouseX,Game.mouseY);
                if(GameHandler.lastChoosenPiece == NULL)
                    GameHandler.ChoosePiece(Game,TemporaryChoosen);
                else
                {
                    if(TemporaryChoosen != NULL)
                        GameHandler.ChoosePiece(Game,TemporaryChoosen);
                    else
                        GameHandler.MovePiece(Game);
                }
            }
        }
        Game.End();
    }
    curBoard->~Sprite();
    Game.~Init();
    return 1;
}

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
Sprite* TemporaryChoosen;
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
        if(GameHandler.lastChoosenSprite != NULL)
        {
            SpriteTile->setPosition(GameHandler.lastChoosenSprite->getX(),GameHandler.lastChoosenSprite->getY());
            GameDrawer.Draw(SpriteTile,Game);
        }
        GameDrawer.DrawVector(Game.getBlackPieces(),Game);
        GameDrawer.DrawVector(Game.getWhitePieces(),Game);
        if(GameHandler.isMouseDown(Game))
        {
            SDL_GetMouseState(&Game.mouseX,&Game.mouseY);
            if(GameHandler.isValidClick(Game))
            {
                GameHandler.initalizeClick(Game);
                TemporaryChoosen = GameHandler.getSpriteInRectangle((GameHandler.turn ? Game.getBlackPieces() : Game.getWhitePieces()),
                                                Game.mouseX / 64,Game.mouseY / 64);
                if(GameHandler.lastChoosenSprite == NULL)
                    GameHandler.lastChoosenSprite = TemporaryChoosen;
                else
                {
                    if(TemporaryChoosen != NULL)
                        GameHandler.lastChoosenSprite = TemporaryChoosen;
                    else
                        GameHandler.MovePiece(Game.mouseX,Game.mouseY);
                }
            }
        }
        Game.End();
    }
    curBoard->~Sprite();
    Game.~Init();
    return 1;
}

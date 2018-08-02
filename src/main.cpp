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
Sprite* BadMoves;
Piece* TemporaryChoosen;

int main( int argc, char * argv[] )
{
    Drawer GameDrawer;
    Init Game;
    GameController GameHandler;
    curBoard = new Sprite(Game.renderer,backgroundImg,0,0,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT);
    SpriteTile = new Sprite(Game.renderer,"ChoosenSprite.png",0,0,64,64);
    BadMoves = new Sprite(Game.renderer,"BadMove.png",156,200,208,62);
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
        if(GameHandler.gameDone)
        {
            Game.End();
            continue;
        }
        if(!GameHandler.turn)
        {
            if(GameHandler.isMouseDown(Game))
            {
                SDL_GetMouseState(&Game.mouseX,&Game.mouseY);
                if(GameHandler.isValidClick(Game))
                {
                    GameHandler.initalizeClick(Game);
                    TemporaryChoosen = Game.Board[GameHandler.lastX/64][GameHandler.lastY/64];
                    if(TemporaryChoosen && TemporaryChoosen->pieceColor != GameHandler.turn)
                        TemporaryChoosen = NULL;
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
        } else
        {
            GameHandler.getNextMove(Game,0,-10000,10000,true,0);
            Game.mouseX = GameHandler.AIX*64;
            Game.mouseY = GameHandler.AIY*64;
            GameHandler.lastChoosenPiece = GameHandler.lastPiece;
            GameHandler.MovePiece(Game);
        }
        if(GameHandler.invalidMoveCounter > 0)
        {
            GameDrawer.Draw(BadMoves,Game);
            GameHandler.invalidMoveCounter--;
        }
        Game.End();
    }
    curBoard->~Sprite();
    Game.~Init();
    return 1;
}
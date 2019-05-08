#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "../Include/Sprite.h"
#include "../Include/Init.h"
#include "../Include/Drawer.h"
#include <vector>
#include "../Include/GameController.h"
#include <bits/stdc++.h>
Sprite* curBoard,*SpriteTile,*BadMoves,*Graveyard;
Piece* TemporaryChoosen;
int main( int numArgs, char *args[]) {
    Drawer GameDrawer;
    Init Game;
    GameController GameHandler;
    curBoard = new Sprite(Game.renderer,"./Sprites/chessBack.bmp",0,0,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT);
    SpriteTile = new Sprite(Game.renderer,"./Sprites/ChoosenSprite.png",0,0,64,64);
    BadMoves = new Sprite(Game.renderer,"./Sprites/BadMove.png",156,200,208,62);
    Graveyard = new Sprite(Game.renderer,"./Sprites/Graveyard.png",512,0,256,512);
    Game.InitializeBlack();
    Game.InitializeWhite();
    SDL_ShowSimpleMessageBox(0,"Info!","S to Save,L to Load,Z to undo,X to Redo,h for help",NULL);
    SDL_ShowSimpleMessageBox(0,"Info!","Press 0 for Player Versus Player,1 for Player Versus Computer",NULL);
    while(!Game.quit && Game.mainEvent->type != SDL_QUIT) {
        SDL_Delay(20);
        Game.Begin();
        GameDrawer.Draw(curBoard,Game);
        GameDrawer.Draw(Graveyard,Game);
        if(GameHandler.lastChoosenPiece != NULL) {
            SpriteTile->setPosition(GameHandler.lastChoosenPiece->getImg()->getX(),GameHandler.lastChoosenPiece->getImg()->getY());
            GameDrawer.Draw(SpriteTile,Game);
        }
        if(GameHandler.TileEffects.size() > 0)
            GameDrawer.DrawSprites(GameHandler.TileEffects,Game);
        GameDrawer.DrawPieces(Game.getPieces(),Game);
        if(GameHandler.isAI == -1) {
            if(Game.mainEvent->type == SDL_KEYDOWN) {
                if(Game.mainEvent->key.keysym.sym == SDLK_0) {
                    GameHandler.isAI = 0;
                    continue;
                } else if(Game.mainEvent->key.keysym.sym == SDLK_1) {
                    GameHandler.isAI = 1;
                    continue;
                } else SDL_ShowSimpleMessageBox(0,"Info!","Press 0 for Player Versus Player,1 for Player Versus Computer",NULL);
            }
            continue;
        }
        if(GameHandler.gameDone) {
            Game.End();
            continue;
        }
        if(GameHandler.checkMate(Game,GameHandler.turn)) {
            if(GameHandler.turn == PIECE_COLOR::BLACK)
                SDL_ShowSimpleMessageBox(0,"Game Done!","White Won!",NULL);
            else
                SDL_ShowSimpleMessageBox(0,"Game Done!","Black Won!",NULL);
            GameHandler.gameDone = true;
            continue;
        }
        if(GameHandler.staleMate(Game,GameHandler.turn)) {
            SDL_ShowSimpleMessageBox(0,"Game Draw!","Draw!",NULL);
            GameHandler.gameDone = true;
            continue;
        }
        if(Game.mainEvent->type == SDL_KEYDOWN && Game.mainEvent->key.keysym.sym == SDLK_h) {
            SDL_ShowSimpleMessageBox(0,"Info!","S to Save,L to Load,Z to undo,X to Redo",NULL);
            continue;
        }
        if(Game.promotionPiece != NULL) {
            if(Game.mainEvent->type == SDL_KEYDOWN) {
                if(GameHandler.promotePiece(Game,Game.promotionPiece,Game.mainEvent->key.keysym.sym)) {
                    Game.promotionPiece = NULL;
                    continue;
                } else  SDL_ShowSimpleMessageBox(0,"Promotion!","press 0 for ROOK,1 for Knight,2 for Bishop,3 for Queen",NULL);
            }
            continue;
        }
        if(Game.mainEvent->type == SDL_KEYDOWN && Game.mainEvent->key.keysym.sym == SDLK_z) {
            GameHandler.undo(Game);
            if(GameHandler.isAI)
                GameHandler.undo(Game);
            continue;
        }
        if(Game.mainEvent->type == SDL_KEYDOWN && Game.mainEvent->key.keysym.sym == SDLK_x) {
            GameHandler.redo(Game);
            if(GameHandler.isAI)
                GameHandler.redo(Game);
            continue;
        }
        if(Game.mainEvent->type == SDL_KEYDOWN && Game.mainEvent->key.keysym.sym == SDLK_s) {
            Game.saveState(GameHandler.turn,GameHandler.isAI);
            SDL_ShowSimpleMessageBox(0,"Save!","State Successfully saved!",NULL);
            continue;
        }
        if(Game.mainEvent->type == SDL_KEYDOWN && Game.mainEvent->key.keysym.sym == SDLK_l) {
            int loadTurn = Game.loadState();
            if(loadTurn == -1)
                continue;
            GameHandler.turn = loadTurn & (1 << 0);
            GameHandler.isAI = loadTurn & (1 << 1);
            GameHandler.lastChoosenPiece = GameHandler.lastPiece = NULL;
            GameHandler.ClearTileEffects(GameHandler.TileEffects);
            GameHandler.clearOperations(GameHandler.redoMove);
            GameHandler.clearOperations(GameHandler.undoMove);
            continue;
        }
        if((GameHandler.turn == PIECE_COLOR::BLACK && GameHandler.isAI) || (!GameHandler.isAI)) {
            if(GameHandler.isMouseDown(Game)) {
                SDL_GetMouseState(&Game.mouseX,&Game.mouseY);
                if(GameHandler.isValidClick(Game)) {
                    GameHandler.initalizeClick(Game);
                    if(GameHandler.lastX/64 >= 8)
                        continue;
                    TemporaryChoosen = Game.Board[GameHandler.lastX/64][GameHandler.lastY/64];
                    if(TemporaryChoosen && TemporaryChoosen->pieceColor != GameHandler.turn)
                        TemporaryChoosen = NULL;
                    if(GameHandler.lastChoosenPiece == NULL)
                        GameHandler.ChoosePiece(Game,TemporaryChoosen);
                    else {
                        if(TemporaryChoosen != NULL)
                            GameHandler.ChoosePiece(Game,TemporaryChoosen);
                        else
                            GameHandler.MovePiece(Game);
                    }
                }
            }
        } else {
            int score = INT_MIN,tmpX = 0,tmpY = 0;
            Piece* piece;
            for(int i = 1; i <= 4; i++) {
                int gameValue = GameHandler.getNextMove(Game,0,PIECE_COLOR::WHITE,i);
                if(score <= gameValue) {
                    score = gameValue;
                    tmpX = Game.mouseX;
                    tmpY = Game.mouseY;
                    piece = GameHandler.lastChoosenPiece;
                }
            }
            Game.mouseX = tmpX;
            Game.mouseY = tmpY;
            GameHandler.lastChoosenPiece = piece;
            GameHandler.ChoosePiece(Game,piece);
            GameHandler.MovePiece(Game);

        }
        if(GameHandler.invalidMoveCounter > 0) {
            GameDrawer.Draw(BadMoves,Game);
            GameHandler.invalidMoveCounter--;
        }
        Game.End();
    }
    curBoard->~Sprite();
    Game.~Init();
    return 1;
}

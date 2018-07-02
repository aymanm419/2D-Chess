#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Sprite.h"
#include "Init.h"
#include "Drawer.h"
#include <vector>
int32_t mouseX,mouseY;
char* backgroundImg = "chessBack.bmp";

std::vector<Sprite*> BlackPieces;
std::vector<Sprite*> WhitePieces;

int main( int argc, char * argv[] )
{
    Drawer GameDrawer;
    Init Game;
    Sprite* curBoard = new Sprite(Game.renderer,backgroundImg,0,0,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT);
    Game.InitializeBlack(BlackPieces);
    Game.InitializeWhite(WhitePieces);
    while(!Game.quit && Game.mainEvent->type != SDL_QUIT)
    {
        Game.Begin();
        GameDrawer.Draw(curBoard,Game);
        SDL_GetMouseState(&mouseX,&mouseY);
        for(std::vector<Sprite*>::iterator it = BlackPieces.begin();it != BlackPieces.end();it++)
            GameDrawer.Draw(*it,Game);
        for(std::vector<Sprite*>::iterator it = WhitePieces.begin();it != WhitePieces.end();it++)
            GameDrawer.Draw(*it,Game);
        Game.End();
    }

    return 1;
}

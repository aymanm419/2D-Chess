#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Sprite.h"
#include "Init.h"
#include "Drawer.h"
#include <vector>
int32_t mouseX,mouseY;
char* backgroundImg = "download.png";
char* ChessImg = "ChessSprite.png";
std::vector<Sprite> WhitePieces;
std::vector<Sprite> BlackPieces;
void InitializeGame(Sprite& Piece)
{
    Piece.setRectDetails(0,0,67,67);
    Piece.setCropDetails(Piece.img_width/6*2,0,Piece.img_width/6,Piece.img_height/2);
}
int main( int argc, char * argv[] )
{
    Init Game;
    Drawer GameDrawer;
    Sprite curBoard(Game.renderer,backgroundImg,0,0,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT);
    Sprite TestPiece(Game.renderer,ChessImg,0,MAX_WINDOWS_HEIGHT/7*0,67,67);
    InitializeGame(TestPiece);
    while(!Game.quit && Game.mainEvent->type != SDL_QUIT)
    {
        Game.Begin();
        GameDrawer.Draw(curBoard,Game);
        GameDrawer.Draw(TestPiece,Game);
        Game.End();
    }
    Game.~Init();
    curBoard.~Sprite();
    return 1;
}

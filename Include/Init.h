#ifndef INIT_H
#define INIT_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include <vector>
#define INF 1000000
#include "Piece.h"
class Init
{
    public:
        Init();
        virtual ~Init();
        bool quit;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event* mainEvent;
        void Begin();
        void End();
        void InitializeBlack();
        void InitializeWhite();
        std::vector<Piece*>& getPieces() {return GamePieces;}
        int32_t mouseX,mouseY;
        Piece* Board[8][8];
    protected:

    private:
        char* ChessImg = "ChessSprite.png";
        int SquareWidth = 64;
        int SquareHeight= 64;
        std::vector<Piece*> GamePieces;

};

#endif // INIT_H

#ifndef INIT_H
#define INIT_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Piece.h"
#define MAX_WINDOWS_WIDTH 512
#define MAX_WINDOWS_HEIGHT 512
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
        void saveState(int turn,int isAI);
        int loadState();
        std::vector<Piece*>& getPieces() {return GamePieces;}
        int TypeToX(int& pieceType);
        int32_t mouseX,mouseY;
        Piece* Board[8][8];
        int deadWhite = 0;
        int deadBlack = 0;
        std::vector<Piece*> GamePieces;
        Piece* promotionPiece;
    protected:

    private:
        char* ChessImg = "./Sprites/ChessSprite.png";
        int SquareWidth = 64;
        int SquareHeight = 64;

};

#endif // INIT_H

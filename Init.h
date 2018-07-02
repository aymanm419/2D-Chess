#ifndef INIT_H
#define INIT_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include <vector>
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
        void InitializeBlack(std::vector<Sprite*>& BlackPieces);
        void InitializeWhite(std::vector<Sprite*>& WhitePieces);

    protected:

    private:
        char* ChessImg = "ChessSprite.png";
        int SquareWidth = 64;
        int SquareHeight= 64;
};

#endif // INIT_H

#ifndef INIT_H
#define INIT_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>

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
    protected:

    private:


};

#endif // INIT_H

#include "Init.h"

Init::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    quit = false;
    window = SDL_CreateWindow("Pay 5$",100,100,600,480,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
        quit = true;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer)
        quit = true;
    mainEvent = new SDL_Event();
}

Init::~Init()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    quit = true;
    delete mainEvent;
}
void Init::Begin()
{
    SDL_PollEvent(mainEvent);
    SDL_RenderClear(renderer);
    return;
}
void Init::End()
{
    SDL_RenderPresent(renderer);
    return;
}

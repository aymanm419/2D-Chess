#include "Init.h"

Init::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    quit = false;
    window = SDL_CreateWindow("Chess Game",100,100,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT,SDL_WINDOW_SHOWN);
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
void Init::InitializeBlack(std::vector<Sprite*>& BlackPieces)
{
    Sprite* Piece;
    for(int i = 2;i <= 4;i++)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*(i-2) ,0,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        BlackPieces.push_back(Piece);
    }
    for(int i = 1;i >= 0;i--)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*(4-i),0,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        BlackPieces.push_back(Piece);
    }
    for(int i = 4;i >= 2;i--)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*(9-i),0,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        BlackPieces.push_back(Piece);
    }
    for(int i = 0;i <= 7;i++)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*5,0,SquareWidth,SquareWidth);
        BlackPieces.push_back(Piece);
    }
}
void Init::InitializeWhite(std::vector<Sprite*>& WhitePieces)
{
    Sprite* Piece;
    for(int i = 2;i <= 4;i++)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*(i-2),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        WhitePieces.push_back(Piece);
    }
    for(int i = 1;i >= 0;i--)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*(4-i),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        WhitePieces.push_back(Piece);
    }
    for(int i = 4;i >= 2;i--)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*(9-i),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        WhitePieces.push_back(Piece);
    }
    for(int i = 0;i <= 7;i++)
    {
        Piece = new Sprite(renderer,ChessImg,0,0,0,0);
        Piece->setRectDetails(SquareWidth*i,MAX_WINDOWS_HEIGHT-2*SquareHeight,SquareWidth,SquareHeight);
        Piece->setCropDetails(SquareWidth*5,SquareHeight,SquareWidth,SquareWidth);
        WhitePieces.push_back(Piece);
    }
}

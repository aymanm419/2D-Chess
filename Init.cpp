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
    for(std::vector<Piece*>::iterator it = GamePieces.begin();it != GamePieces.end();it++)
    {
        (*it)->PieceImg->~Sprite();
        (*it)->~Piece();
        delete (*it);
    }
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
void Init::InitializeBlack()
{
    Sprite* Pi;
    Piece* temporaryPiece;
    for(int i = 2;i <= 4;i++)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(i-2) ,0,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(true,i-2);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 1;i >= 0;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(4-i),0,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(true,4-i);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 4;i >= 2;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(9-i),0,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(true,i-2);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 0;i <= 7;i++)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*5,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(true,5);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
}
void Init::InitializeWhite()
{
    Sprite* Pi;
    Piece* temporaryPiece;
    for(int i = 2;i <= 4;i++)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(i-2),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(false,i-2);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 1;i >= 0;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(4-i),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(false,4-i);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 4;i >= 2;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(9-i),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(false,i-2);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 0;i <= 7;i++)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*i,MAX_WINDOWS_HEIGHT-2*SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*5,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(false,5);
        temporaryPiece->PieceImg = Pi;
        GamePieces.push_back(temporaryPiece);
    }
}

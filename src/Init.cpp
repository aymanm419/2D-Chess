#include "../Include/Init.h"
#include <fstream>
#include <iostream>
Init::Init()
{
    SDL_Init(SDL_INIT_VIDEO);
    quit = false;
    window = SDL_CreateWindow("Chess Game",100,100,MAX_WINDOWS_WIDTH+256,MAX_WINDOWS_HEIGHT,SDL_WINDOW_SHOWN);
    if(window == NULL)
        quit = true;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(!renderer)
        quit = true;
    mainEvent = new SDL_Event();
    for(int i = 0;i < 8;i++)
        for(int j = 0;j < 8;j++)
            Board[i][j] = NULL;
    promotionPiece = NULL;
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
        Pi->setRectDetails(SquareWidth*(i-2),0,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::BLACK,i-2);
        temporaryPiece->PieceImg = Pi;
        Board[(i-2)][0] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 1;i >= 0;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(4-i),0,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::BLACK,4-i);
        temporaryPiece->PieceImg = Pi;
        Board[(4-i)][0] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 4;i >= 2;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(9-i),0,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::BLACK,i-2);
        temporaryPiece->PieceImg = Pi;
        Board[(9-i)][0] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 0;i <= 7;i++)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*5,0,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::BLACK,5);
        temporaryPiece->PieceImg = Pi;
        Board[i][1] = temporaryPiece;
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
        temporaryPiece = new Piece(PIECE_COLOR::WHITE,i-2);
        temporaryPiece->PieceImg = Pi;
        Board[(i-2)][7] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 1;i >= 0;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(4-i),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::WHITE,4-i);
        temporaryPiece->PieceImg = Pi;
        Board[(4-i)][7] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 4;i >= 2;i--)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*(9-i),MAX_WINDOWS_HEIGHT-SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*i,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::WHITE,i-2);
        temporaryPiece->PieceImg = Pi;
        Board[(9-i)][7] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
    for(int i = 0;i <= 7;i++)
    {
        Pi = new Sprite(renderer,ChessImg,0,0,0,0);
        Pi->setRectDetails(SquareWidth*i,MAX_WINDOWS_HEIGHT-2*SquareHeight,SquareWidth,SquareHeight);
        Pi->setCropDetails(SquareWidth*5,SquareHeight,SquareWidth,SquareWidth);
        temporaryPiece = new Piece(PIECE_COLOR::WHITE,5);
        temporaryPiece->PieceImg = Pi;
        Board[i][6] = temporaryPiece;
        GamePieces.push_back(temporaryPiece);
    }
}
int Init::TypeToX(int& pieceType)
{
    if(pieceType == PIECE_TYPE::KING)
        return 0;
    if(pieceType == PIECE_TYPE::QUEEN)
        return 64;
    if(pieceType == PIECE_TYPE::ROOK)
        return 64*2;
    if(pieceType == PIECE_TYPE::KNIGHT)
        return 64*3;
    if(pieceType == PIECE_TYPE::BISHOP)
        return 64*4;
    return 64*5;
}
void Init::saveState(int turn,int isAI)
{
    std::ofstream myfile;
    myfile.open("save.txt");
    myfile.clear();
    myfile << turn << " " << isAI << "\n";
    for(std::vector<Piece*>::iterator it = GamePieces.begin();it != GamePieces.end();it++)
        myfile << ((*it)->pieceColor) << " " << ((*it))->PieceType << " " << (*it)->getImg()->getX() << " " << (*it)->getImg()->getY() << "\n";
    myfile.close();
}
int Init::loadState()
{
    std::ifstream myfile("save.txt");
    if(!myfile.is_open())
    {
        SDL_ShowSimpleMessageBox(NULL,"Error!","File not found to load from",NULL);
        return -1;
    }
    for(int i = 0;i < 8;i++)
    {
        for(int j = 0;j < 8;j++)
            Board[i][j] = NULL;
    }
    for(std::vector<Piece*>::iterator it = GamePieces.begin();it != GamePieces.end();it++)
        delete (*it);
    GamePieces.clear();
    deadBlack = deadWhite = 0;
    int turn,IsAi;
    myfile >> turn >> IsAi;
    int flg = 0;
    if(turn)
        flg |= (1 << 0);
    if(IsAi)
        flg |= (1 << 1);
    int tmpC,tmpT,tmpX,tmpY;
    while(myfile >> tmpC >> tmpT >> tmpX >> tmpY)
    {
        Piece* tmpPiece = new Piece(tmpC,tmpT);
        Sprite* tmpSprite = new Sprite(renderer,"./Sprites/ChessSprite.png",tmpX*64,tmpY*64,SquareWidth,SquareHeight);
        tmpSprite->setCropDetails(TypeToX(tmpT),tmpC*64,SquareWidth,SquareHeight);
        tmpPiece->PieceImg = tmpSprite;
        if(tmpX < 8 && tmpY < 8)
            Board[tmpX][tmpY] = tmpPiece;
        if(tmpX >= 8)
        {
            if(tmpC == PIECE_COLOR::BLACK)
                deadBlack++;
            else
                deadWhite++;
            tmpPiece->isDead = true;
        }
        GamePieces.push_back(tmpPiece);
    }
    SDL_ShowSimpleMessageBox(NULL,"Success!","File Loaded successfully!",NULL);
    myfile.close();
    return flg;
}

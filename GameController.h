#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "Init.h"
#include "Piece.h"
#include "Drawer.h"
class GameController
{
    public:
        GameController();
        bool isMouseDown(Init& Game);
        bool isValidClick(Init& Game);
        void initalizeClick(Init& Game);
        std::pair<int,int> getRectangle(int X,int Y);
        void AddHorizontalTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void AddVerticalPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void AddAroundKingTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void AddDiagonalPositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void AddKnightPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void AddHorsePositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void MovePiece(Init& game);
        void ChoosePiece(Init& game,Piece* piece);
        bool validMove(int gotoX,int gotoY);
        bool checkMate(Init& game);
        void addTilesPerPiece(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec,bool cturn);
        void removePiece(Init& game,Piece* piece);
        void ClearTileEffects(std::vector<Sprite*>& SpritesVec);
        int getBoardScore(Init& game);
        void fillTileEffects(Init& game,std::vector<std::pair<int,int> >& PositionVector);
        int getNextMove(Init& game,int depth,int alpha,int beta,bool curTurn);
        bool turn,gameDone;
        Piece* lastChoosenPiece;
        Piece* lastPiece;
        int AIX,AIY;
        std::vector<Sprite*> TileEffects;
        int32_t lastX,lastY;
    protected:

    private:


};

#endif // GAMECONTROLLER_H

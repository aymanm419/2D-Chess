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
        Piece* getPieceInRectangle(std::vector<Piece*>& PiecesVector,int PosX,int PosY,bool ignoreColor = false);
        void AddHorizontalTiles(Init& game,Piece* piece);
        void AddVerticalPosition(Init& game,Piece* piece);
        void AddAroundKingTiles(Init& game,Piece* piece);
        void AddDiagonalPositions(Init& game,Piece* piece);
        void AddKnightPosition(Init& game,Piece* piece);
        void AddHorsePositions(Init& game,Piece* piece);
        void MovePiece(Init& game);
        void ChoosePiece(Init& game,Piece* piece);
        bool validMove(int gotoX,int gotoY);
        bool checkMate(Init& game);
        void addTilesPerPiece(Init& game,Piece* piece);
        void removePiece(Init& game,Piece* piece);
        void ClearTileEffects();
        bool turn;
        Piece* lastChoosenPiece;
        std::vector<Sprite*> TileEffects;
    protected:

    private:
        int32_t lastX,lastY;

};

#endif // GAMECONTROLLER_H

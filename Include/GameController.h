#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "Init.h"
#include "Piece.h"
#include "Drawer.h"
struct operation
{
    Piece* attacker = NULL;
    Piece* attacked = NULL;
    int fromX,fromY;
    int toX,toY;
    bool promotion = false;
    void setOp(Piece* f1,Piece* f2,int fx,int fy,int tx,int ty,bool p)
    {
        attacker = f1;
        attacked = f2;
        fromX = fx;
        fromY = fy;
        toX = tx;
        toY = ty;
        promotion = p;
    }
};
class GameController
{
    public:
        GameController();
        bool isMouseDown(Init& Game);
        bool isValidClick(Init& Game);
        void initalizeClick(Init& Game);
        std::pair<int,int> getRectangle(int X,int Y);
        void AddHorizontalTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void AddVerticalPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void AddAroundKingTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void AddDiagonalPositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void AddKnightPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void AddHorsePositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void MovePiece(Init& game);
        void ChoosePiece(Init& game,Piece* piece);
        bool validMove(int gotoX,int gotoY);
        bool check(Init& game,int kingColor);
        void addTilesPerPiece(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec);
        void killPiece(Init& game,Piece* piece);
        void unkillPiece(Init& game,Piece* piece,int oldX,int oldY);
        void ClearTileEffects(std::vector<Sprite*>& SpritesVec);
        int getBoardScore(int oldX,int oldY,int newX,int newY);
        void fillTileEffects(Init& game,std::vector<std::pair<int,int> >& PositionVector);
        int getNextMove(Init& game,int depth,bool curTurn);
        bool checkMate(Init& game,int kingColor);
        bool staleMate(Init& game,int kingColor);
        bool promotePiece(Init& game,Piece* piece,SDL_Keycode buttonClicked);
        void clearOperations(std::vector<operation*>& op);
        void undo(Init& game);
        void redo(Init& game);
        bool turn,gameDone;
        Piece* lastChoosenPiece;
        Piece* lastPiece;
        int AIX,AIY,alivePieces;
        std::vector<Sprite*> TileEffects;
        std::vector<operation*> undoMove,redoMove;
        int32_t lastX,lastY;
        int32_t invalidMoveCounter;
        int isAI;
    protected:

    private:


};

#endif // GAMECONTROLLER_H

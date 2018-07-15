#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "Init.h"

class GameController
{
    public:
        GameController();
        bool isMouseDown(Init& Game);
        bool isValidClick(Init& Game);
        void initalizeClick(Init& Game);
        std::pair<int,int> getRectangle(int X,int Y);
        Sprite* getSpriteInRectangle(std::vector<Sprite*>& PiecesVector,int PosX,int PosY);
        bool MovePiece(int MoveX,int MoveY);
        Sprite* lastChoosenSprite;
        bool turn;
    protected:

    private:
        int32_t lastX,lastY;

};

#endif // GAMECONTROLLER_H

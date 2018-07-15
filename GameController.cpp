#include "GameController.h"
#include "Init.h"

GameController::GameController()
{
    turn = false;
    lastChoosenSprite = NULL;
}
bool GameController::isMouseDown(Init& Game)
{
    return Game.mainEvent->type == SDL_MOUSEBUTTONDOWN && Game.mainEvent->button.button == SDL_BUTTON_LEFT;
}

bool GameController::isValidClick(Init& Game)
{
    return (Game.mouseX != lastX || Game.mouseY != lastY);
}

void GameController::initalizeClick(Init& Game)
{
    lastX = Game.mouseX;
    lastY = Game.mouseY;
}
std::pair<int,int> GameController::getRectangle(int X,int Y)
{
    return std::make_pair(X / 64,Y / 64);
}
Sprite* GameController::getSpriteInRectangle(std::vector<Sprite*>& PiecesVector,int PosX,int PosY)
{
    for(std::vector<Sprite*>::iterator it = PiecesVector.begin();it != PiecesVector.end();it++)
    {
        std::pair<int,int> PieceRectangle = getRectangle((*it)->getX(),(*it)->getY());
        if(PieceRectangle.first == PosX && PieceRectangle.second == PosY)
            return (*it);
    }
    return NULL;
}
bool GameController::MovePiece(int MoveX,int MoveY)
{
    lastChoosenSprite->setPosition(MoveX/64 * 64,MoveY/64 * 64);
    turn = !turn;
    lastChoosenSprite = NULL;
}


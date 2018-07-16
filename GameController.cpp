#include "GameController.h"
#include "Init.h"
#include <cmath>
#include <iostream>
GameController::GameController()
{
    turn = false;
    lastChoosenPiece = NULL;
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
Piece* GameController::getPieceInRectangle(std::vector<Piece*>& PiecesVector,int PosX,int PosY,bool ignoreColor)
{
    PosX /= 64;
    PosY /= 64;
    for(std::vector<Piece*>::iterator it = PiecesVector.begin();it != PiecesVector.end();it++)
    {
        Sprite* curSprite = (*it)->getImg();
        std::pair<int,int> PieceRectangle = getRectangle(curSprite->getX(),curSprite->getY());
        if(PieceRectangle.first == PosX && PieceRectangle.second == PosY)
        {
            if(ignoreColor)
                return (*it);
            else if(turn == (*it)->pieceColor)
                return (*it);
        }
    }
    return NULL;
}
void GameController::AddHorizontalTiles(Init& game,Piece* piece)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX + i*64;
        if(newX > MAX_WINDOWS_WIDTH)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,curY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,curY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,curY,64,64));
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX - i*64;
        if(newX < 0)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,curY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,curY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,curY,64,64));
            break;
        }
    }
}
void GameController::AddVerticalPosition(Init& game,Piece* piece)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1;i <= 8;i++)
    {
        int newY = curY + i*64;
        if(newY > MAX_WINDOWS_HEIGHT)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),curX,newY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",curX,newY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",curX,newY,64,64));
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newY = curY - i*64;
        if(newY < 0)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),curX,newY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",curX,newY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",curX,newY,64,64));
            break;
        }
    }
}
void GameController::AddKnightPosition(Init& game,Piece* piece)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    if(!piece->pieceColor)
    {
        for(int i = 1;i <= 2;i++)
        {
            int newY = curY - i*64;
            if(newY < 0)
                break;
            if(i == 2 && curY != 384)
                break;
            Piece* curPiece = getPieceInRectangle(game.getPieces(),curX,newY,true);
            if(curPiece == NULL)
                TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",curX,newY,64,64));
        }
        for(int i = -1;i <= 1;i += 2)
        {
            int newY = curY - 64;
            int newX = curX + i*64;
            if(newY < 0 || newX < 0 || newX > MAX_WINDOWS_WIDTH)
                continue;
            Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
            if(curPiece != NULL && curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
        }
    } else
    {
        for(int i = 1;i <= 2;i++)
        {
            int newY = curY + i*64;
            if(newY > MAX_WINDOWS_HEIGHT)
                break;
            if(i == 2 && curY != 64)
                break;
            Piece* curPiece = getPieceInRectangle(game.getPieces(),curX,newY,true);
            if(curPiece == NULL)
                TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",curX,newY,64,64));
        }
        for(int i = -1;i <= 1;i += 2)
        {
            int newY = curY + 64;
            int newX = curX + i*64;
            if(newY > MAX_WINDOWS_HEIGHT || newX < 0 || newX > MAX_WINDOWS_WIDTH)
                continue;
            Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
            if(curPiece != NULL && curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
        }
    }
}
void GameController::AddHorsePositions(Init& game,Piece* piece)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = -2;i <= 2;i++)
    {
        for(int j = -2;j <= 2;j++)
        {
            if(std::abs(i*j) != 2)
                continue;
            int newX = curX + j*64;
            int newY = curY + i*64;
            if(newY > MAX_WINDOWS_HEIGHT || newY < 0 || newX < 0 || newX > MAX_WINDOWS_WIDTH)
                continue;
            Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
            if(curPiece == NULL)
                TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,newY,64,64));
            else
            {
                if(curPiece->pieceColor != piece->pieceColor)
                    TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
                continue;
            }
        }
    }
}
void GameController::AddAroundKingTiles(Init& game,Piece* piece)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = -1;i <= 1;i++)
    {
        for(int j = -1;j <= 1;j++)
        {
            int newX = curX + i*64;
            int newY = curY + j*64;
            if(newY > MAX_WINDOWS_HEIGHT || newY < 0 || newX < 0 || newX > MAX_WINDOWS_WIDTH)
                continue;
            if(newX == curX && newY == curY)
                continue;
            Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
            if(curPiece == NULL)
                TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,newY,64,64));
            else
            {
                if(curPiece->pieceColor != piece->pieceColor)
                    TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
                continue;
            }
        }
    }
}
void GameController::AddDiagonalPositions(Init& game,Piece* piece)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX + i*64;
        int newY = curY + i*64;
        if(newY > MAX_WINDOWS_HEIGHT || newX > MAX_WINDOWS_WIDTH)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,newY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY ,64,64));
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX - i*64;
        int newY = curY - i*64;
        if(newY < 0 || newX < 0)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,newY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX + i*64;
        int newY = curY - i*64;
        if(newY < 0 || newX > MAX_WINDOWS_WIDTH)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,newY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX - i*64;
        int newY = curY + i*64;
        if(newY > MAX_WINDOWS_WIDTH || newX < 0)
            break;
        Piece* curPiece = getPieceInRectangle(game.getPieces(),newX,newY,true);
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",newX,newY,64,64));
        else
        {
            if(curPiece->pieceColor != piece->pieceColor)
                TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",newX,newY,64,64));
            break;
        }
    }
}
void GameController::ClearTileEffects()
{
    if(TileEffects.size() > 0)
    {
        for(std::vector<Sprite*>::iterator it = TileEffects.begin();it != TileEffects.end();it++)
            delete (*it);
    }
    TileEffects.clear();
}
void GameController::ChoosePiece(Init& game,Piece* piece)
{
    ClearTileEffects();
    lastChoosenPiece = piece;
    if(lastChoosenPiece == NULL)
        return;
    int curType = piece->PieceType;
    if(curType == 0 || curType == 3)
    {
        AddHorizontalTiles(game,piece);
        AddVerticalPosition(game,piece);
    }
    if(curType == 3 || curType == 2)
        AddDiagonalPositions(game,piece);
    if(curType == 4)
        AddAroundKingTiles(game,piece);
    if(curType == 1)
        AddHorsePositions(game,piece);
    if(curType == 5)
        AddKnightPosition(game,piece);

}
bool GameController::validMove(int gotoX,int gotoY)
{
    for(std::vector<Sprite*>::iterator it = TileEffects.begin();it != TileEffects.end();it++)
    {
        if(gotoX == (*it)->getX() && gotoY == (*it)->getY())
            return true;
    }
    return false;
}
void GameController::removePiece(Init& game,Piece* piece)
{
    for(std::vector<Piece*>::iterator it = game.getPieces().begin();it != game.getPieces().end();it++)
    {
        if(piece == (*it))
        {
            (*it)->~Piece();
            game.getPieces().erase(it);
            break;
        }
    }
    return;
}
void GameController::MovePiece(Init& game)
{
    int MoveX = (game.mouseX/64)*64;
    int MoveY = (game.mouseY/64)*64;
    if(!validMove(MoveX,MoveY))
        return;
    Piece* curPiece = getPieceInRectangle(game.getPieces(),MoveX,MoveY,true);
    if(curPiece != NULL)
        removePiece(game,curPiece);
    lastChoosenPiece->getImg()->setPosition(MoveX,MoveY);
    turn = !turn;
    lastChoosenPiece = NULL;
    ClearTileEffects();
}


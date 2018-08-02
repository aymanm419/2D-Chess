#include "GameController.h"
#include "Init.h"
#include <cmath>
#include <iostream>
#include <windows.h>
GameController::GameController()
{
    turn = gameDone = false;
    lastChoosenPiece = NULL;
    lastPiece = NULL;
    invalidMoveCounter = 0;
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
void GameController::AddHorizontalTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX + i;
        if(newX >= 8)
            break;
        SpritesVec.push_back(std::make_pair(newX,curY));
        if(game.Board[newX][curY])
        {
            if(game.Board[newX][curY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX - i;
        if(newX < 0)
            break;
        SpritesVec.push_back(std::make_pair(newX,curY));
        if(game.Board[newX][curY])
        {
            if(game.Board[newX][curY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
}
void GameController::AddVerticalPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1;i <= 8;i++)
    {
        int newY = curY + i;
        if(newY >= 8)
            break;
        SpritesVec.push_back(std::make_pair(curX,newY));
        if(game.Board[curX][newY])
        {
            if(game.Board[curX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newY = curY - i;
        if(newY < 0)
            break;
        SpritesVec.push_back(std::make_pair(curX,newY));
        if(game.Board[curX][newY])
        {
            if(game.Board[curX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
}
void GameController::AddKnightPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    if(!piece->pieceColor)
    {
        for(int i = 1;i <= 2;i++)
        {
            int newY = curY - i;
            if(newY < 0)
                break;
            if(i == 2 && curY != 6)
                break;
            SpritesVec.push_back(std::make_pair(curX,newY));
            if(game.Board[curX][newY])
            {
                SpritesVec.pop_back();
                break;
            }
        }
        for(int i = -1;i <= 1;i += 2)
        {
            int newY = curY - 1;
            int newX = curX + i;
            if(newY < 0 || newX < 0 || newX >= 8)
                continue;
            if(game.Board[newX][newY] && game.Board[newX][newY]->pieceColor != piece->pieceColor)
                SpritesVec.push_back(std::make_pair(newX,newY));
        }
    } else
    {
        for(int i = 1;i <= 2;i++)
        {
            int newY = curY + i;
            if(newY >= 8)
                break;
            if(i == 2 && curY != 1)
                break;
            SpritesVec.push_back(std::make_pair(curX,newY));
            if(game.Board[curX][newY])
            {
                SpritesVec.pop_back();
                break;
            }
        }
        for(int i = -1;i <= 1;i += 2)
        {
            int newY = curY + 1;
            int newX = curX + i;
            if(newY >= 8 || newX < 0 || newX >= 8)
                continue;
            if(game.Board[newX][newY] && game.Board[newX][newY]->pieceColor != piece->pieceColor)
                SpritesVec.push_back(std::make_pair(newX,newY));
        }
    }
}
void GameController::AddHorsePositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = -2;i <= 2;i++)
    {
        for(int j = -2;j <= 2;j++)
        {
            if(std::abs(i*j) != 2)
                continue;
            int newX = curX + j;
            int newY = curY + i;
            if(newY >= 8 || newY < 0 || newX < 0 || newX >= 8)
                continue;
            SpritesVec.push_back(std::make_pair(newX,newY));
            if(game.Board[newX][newY])
            {
                if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                    SpritesVec.pop_back();
                continue;
            }
        }
    }
}
void GameController::AddAroundKingTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = -1;i <= 1;i++)
    {
        for(int j = -1;j <= 1;j++)
        {
            int newX = curX + i;
            int newY = curY + j;
            if(newY >= 8 || newY < 0 || newX < 0 || newX >= 8)
                continue;
            if(newX == curX && newY == curY)
                continue;
            SpritesVec.push_back(std::make_pair(newX,newY));
            if(game.Board[newX][newY])
            {
                if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                    SpritesVec.pop_back();
                continue;
            }
        }
    }
}
void GameController::AddDiagonalPositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX + i;
        int newY = curY + i;
        if(newY >= 8 || newX >= 8)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY])
        {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX - i;
        int newY = curY - i;
        if(newY < 0 || newX < 0)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY])
        {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX + i;
        int newY = curY - i;
        if(newY < 0 || newX >= 8)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY])
        {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1;i <= 8;i++)
    {
        int newX = curX - i;
        int newY = curY + i;
        if(newY >= 8 || newX < 0)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY])
        {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
}
void GameController::ClearTileEffects(std::vector<Sprite*>& SpritesVec)
{
    if(SpritesVec.size() > 0)
    {
        for(std::vector<Sprite*>::iterator it = SpritesVec.begin();it != SpritesVec.end();it++)
            delete (*it);
    }
    SpritesVec.clear();
}
void GameController::addTilesPerPiece(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec)
{
    int curType = piece->PieceType;
    if(curType == 0 || curType == 3)
    {
        AddHorizontalTiles(game,piece,SpritesVec);
        AddVerticalPosition(game,piece,SpritesVec);
    }
    if(curType == 3 || curType == 2)
        AddDiagonalPositions(game,piece,SpritesVec);
    if(curType == 4)
        AddAroundKingTiles(game,piece,SpritesVec);
    if(curType == 1)
        AddHorsePositions(game,piece,SpritesVec);
    if(curType == 5)
        AddKnightPosition(game,piece,SpritesVec);
}
void GameController::fillTileEffects(Init& game,std::vector<std::pair<int,int> >& PositionVector)
{
    for(std::vector<std::pair<int,int> >::iterator it = PositionVector.begin();it != PositionVector.end();it++)
    {
        int curX = (*it).first;
        int curY = (*it).second;
        Piece* curPiece = game.Board[curX][curY];
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"AllowedSprite.png",curX*64,curY*64,64,64));
        else
            TileEffects.push_back(new Sprite(game.renderer,"AttackSprite.png",curX*64,curY*64,64,64));
    }
}
void GameController::ChoosePiece(Init& game,Piece* piece)
{
    if(piece == NULL)
        return;
    if(piece->pieceColor != turn)
        return;
    ClearTileEffects(TileEffects);
    lastChoosenPiece = piece;
    if(lastChoosenPiece == NULL)
        return;
    std::vector<std::pair<int,int> > positionVector;
    addTilesPerPiece(game,lastChoosenPiece,positionVector);
    fillTileEffects(game,positionVector);
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
    piece->isDead = true;
    return;
}
bool GameController::checkMate(Init& game)
{
    int kingX,kingY;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin();it != game.getPieces().end();it++)
    {
        if((*it)->pieceColor == turn && (*it)->PieceType == 4)
        {
            kingX = (*it)->getImg()->getX();
            kingY = (*it)->getImg()->getY();
            break;
        }
    }
    std::vector<std::pair<int,int> > PossiblePositions;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin();it != game.getPieces().end();it++)
    {
        if((*it)->pieceColor != turn && !(*it)->isDead)
            addTilesPerPiece(game,(*it),PossiblePositions);
    }
    for(std::vector<std::pair<int,int> >::iterator it = PossiblePositions.begin();it != PossiblePositions.end();it++)
    {
        if(kingX == (*it).first && kingY == (*it).second)
            return true;
    }
    return false;
}
int GameController::getBoardScore(Init& game)
{
    int delta = 0;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin();it != game.getPieces().end();it++)
    {
        if((*it)->pieceColor)
            delta += (*it)->getPieceValue() * ((*it)->isDead ? -1 : 1);
        else
            delta += (*it)->getPieceValue() * (!(*it)->isDead ? -1 : 1);
    }
    return delta;
}
//1 for Player King,2 for AI King
int GameController::getNextMove(Init& game,int depth,int alpha,int beta,bool curTurn,int kingDead)
{
    if(depth == 4)
        return getBoardScore(game) - depth;
    int BestCur = (curTurn ? -3000 : 3000);
    bool bk = false;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin();it != game.getPieces().end();it++)
    {
        if((*it)->isDead || (*it)->pieceColor != curTurn)
            continue;
        if(bk)
            break;
        std::vector<std::pair<int,int> > availablePositions;
        addTilesPerPiece(game,*it,availablePositions);
        int oldX = (*it)->getImg()->getX();
        int oldY = (*it)->getImg()->getY();
        for(int i = 0;i < availablePositions.size();i++)
        {
            if(bk)
                break;
            int newX = availablePositions[i].first;
            int newY = availablePositions[i].second;
            Piece* attackedPiece = game.Board[newX][newY];
            if(attackedPiece)
            {
                attackedPiece->isDead = true;
                if(attackedPiece->getPieceValue() == 3000)
                    kingDead = (curTurn ? 1 : 2);
            }
            game.Board[newX][newY] = *it;
            game.Board[oldX][oldY] = NULL;
            (*it)->getImg()->setPosition(newX,newY);
            int val = getNextMove(game,depth + 1,alpha,beta,!curTurn,kingDead);
            if(curTurn)
            {
                alpha = std::max(alpha,val);
                if(val >= BestCur)
                {
                    BestCur = val;
                    if(depth == 0)
                    {
                        lastPiece = *it;
                        AIX = newX;
                        AIY = newY;
                    }
                }
                if(alpha > beta && depth != 0)
                    bk = true;
            } else
            {
                BestCur = std::min(BestCur,val);
                beta = std::min(beta,val);
                if(alpha > beta && depth != 0)
                    bk = true;
            }
            if(attackedPiece)
            {
                attackedPiece->isDead = false;
                if(attackedPiece->getPieceValue() == 3000)
                    kingDead = 0;
            }
            (*it)->getImg()->setPosition(oldX,oldY);
            game.Board[newX][newY] = attackedPiece;
            game.Board[oldX][oldY] = *it;
        }
    }
    return BestCur;
}
void GameController::MovePiece(Init& game)
{
    int MoveX = (game.mouseX/64);
    int MoveY = (game.mouseY/64);
    if(!validMove(MoveX,MoveY) && !turn)
        return;
    int lastX = lastChoosenPiece->getImg()->getX();
    int lastY = lastChoosenPiece->getImg()->getY();
    Piece* curPiece = game.Board[MoveX][MoveY];
    if(curPiece != NULL)
        curPiece->isDead = true;
    lastChoosenPiece->getImg()->setPosition(MoveX,MoveY);
    game.Board[MoveX][MoveY] = game.Board[lastX][lastY];
    game.Board[lastX][lastY] = NULL;
    if(!turn && checkMate(game))
    {
        if(curPiece != NULL)
            curPiece->isDead = false;
        lastChoosenPiece->getImg()->setPosition(lastX,lastY);
        invalidMoveCounter = 1000;
        game.Board[MoveX][MoveY] = curPiece;
        game.Board[lastX][lastY] = lastChoosenPiece;
        return;
    }
    if(curPiece != NULL)
    {
        removePiece(game,curPiece);
        if(curPiece->PieceType == 4)
            gameDone = true;
    }
    turn = !turn;
    lastChoosenPiece = NULL;
    ClearTileEffects(TileEffects);
}

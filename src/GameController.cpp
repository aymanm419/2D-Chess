#include "../Include/GameController.h"
#include "../Include/Init.h"
#include <cmath>
#include <iostream>
#include <windows.h>
GameController::GameController() {
    gameDone = false;
    turn = PIECE_COLOR::WHITE;
    lastChoosenPiece = NULL;
    lastPiece = NULL;
    invalidMoveCounter = 0;
    alivePieces = 32;
    isAI = -1;
}
bool GameController::isMouseDown(Init& Game) {
    return Game.mainEvent->type == SDL_MOUSEBUTTONDOWN && Game.mainEvent->button.button == SDL_BUTTON_LEFT;
}

bool GameController::isValidClick(Init& Game) {
    return (Game.mouseX != lastX || Game.mouseY != lastY);
}

void GameController::initalizeClick(Init& Game) {
    lastX = Game.mouseX;
    lastY = Game.mouseY;
}
void GameController::AddHorizontalTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1; i <= 8; i++) {
        int newX = curX + i;
        if(newX >= 8)
            break;
        SpritesVec.push_back(std::make_pair(newX,curY));
        if(game.Board[newX][curY]) {
            if(game.Board[newX][curY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1; i <= 8; i++) {
        int newX = curX - i;
        if(newX < 0)
            break;
        SpritesVec.push_back(std::make_pair(newX,curY));
        if(game.Board[newX][curY]) {
            if(game.Board[newX][curY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
}
void GameController::AddVerticalPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1; i <= 8; i++) {
        int newY = curY + i;
        if(newY >= 8)
            break;
        SpritesVec.push_back(std::make_pair(curX,newY));
        if(game.Board[curX][newY]) {
            if(game.Board[curX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1; i <= 8; i++) {
        int newY = curY - i;
        if(newY < 0)
            break;
        SpritesVec.push_back(std::make_pair(curX,newY));
        if(game.Board[curX][newY]) {
            if(game.Board[curX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
}
void GameController::AddKnightPosition(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    if(piece->pieceColor == PIECE_COLOR::WHITE) {
        for(int i = 1; i <= 2; i++) {
            int newY = curY - i;
            if(newY < 0)
                break;
            if(i == 2 && curY != 6)
                break;
            SpritesVec.push_back(std::make_pair(curX,newY));
            if(game.Board[curX][newY]) {
                SpritesVec.pop_back();
                break;
            }
        }
        for(int i = -1; i <= 1; i += 2) {
            int newY = curY - 1;
            int newX = curX + i;
            if(newY < 0 || newX < 0 || newX >= 8)
                continue;
            if(game.Board[newX][newY] && game.Board[newX][newY]->pieceColor != piece->pieceColor)
                SpritesVec.push_back(std::make_pair(newX,newY));
        }
    } else {
        for(int i = 1; i <= 2; i++) {
            int newY = curY + i;
            if(newY >= 8)
                break;
            if(i == 2 && curY != 1)
                break;
            SpritesVec.push_back(std::make_pair(curX,newY));
            if(game.Board[curX][newY]) {
                SpritesVec.pop_back();
                break;
            }
        }
        for(int i = -1; i <= 1; i += 2) {
            int newY = curY + 1;
            int newX = curX + i;
            if(newY >= 8 || newX < 0 || newX >= 8)
                continue;
            if(game.Board[newX][newY] && game.Board[newX][newY]->pieceColor != piece->pieceColor)
                SpritesVec.push_back(std::make_pair(newX,newY));
        }
    }
}
void GameController::AddHorsePositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = -2; i <= 2; i++) {
        for(int j = -2; j <= 2; j++) {
            if(std::abs(i*j) != 2)
                continue;
            int newX = curX + j;
            int newY = curY + i;
            if(newY >= 8 || newY < 0 || newX < 0 || newX >= 8)
                continue;
            SpritesVec.push_back(std::make_pair(newX,newY));
            if(game.Board[newX][newY]) {
                if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                    SpritesVec.pop_back();
                continue;
            }
        }
    }
}
void GameController::AddAroundKingTiles(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
            int newX = curX + i;
            int newY = curY + j;
            if(newY >= 8 || newY < 0 || newX < 0 || newX >= 8)
                continue;
            if(newX == curX && newY == curY)
                continue;
            SpritesVec.push_back(std::make_pair(newX,newY));
            if(game.Board[newX][newY]) {
                if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                    SpritesVec.pop_back();
                continue;
            }
        }
    }
}
void GameController::AddDiagonalPositions(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curX = piece->getImg()->getX();
    int curY = piece->getImg()->getY();
    for(int i = 1; i <= 8; i++) {
        int newX = curX + i;
        int newY = curY + i;
        if(newY >= 8 || newX >= 8)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY]) {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1; i <= 8; i++) {
        int newX = curX - i;
        int newY = curY - i;
        if(newY < 0 || newX < 0)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY]) {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1; i <= 8; i++) {
        int newX = curX + i;
        int newY = curY - i;
        if(newY < 0 || newX >= 8)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY]) {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
    for(int i = 1; i <= 8; i++) {
        int newX = curX - i;
        int newY = curY + i;
        if(newY >= 8 || newX < 0)
            break;
        SpritesVec.push_back(std::make_pair(newX,newY));
        if(game.Board[newX][newY]) {
            if(game.Board[newX][newY]->pieceColor == piece->pieceColor)
                SpritesVec.pop_back();
            break;
        }
    }
}
void GameController::ClearTileEffects(std::vector<Sprite*>& SpritesVec) {
    if(SpritesVec.size() > 0) {
        for(std::vector<Sprite*>::iterator it = SpritesVec.begin(); it != SpritesVec.end(); it++)
            delete (*it);
    }
    SpritesVec.clear();
}
void GameController::addTilesPerPiece(Init& game,Piece* piece,std::vector<std::pair<int,int> >& SpritesVec) {
    int curType = piece->PieceType;
    if(curType == 0 || curType == 3) {
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
void GameController::fillTileEffects(Init& game,std::vector<std::pair<int,int> >& PositionVector) {
    for(std::vector<std::pair<int,int> >::iterator it = PositionVector.begin(); it != PositionVector.end(); it++) {
        int curX = (*it).first;
        int curY = (*it).second;
        Piece* curPiece = game.Board[curX][curY];
        if(curPiece == NULL)
            TileEffects.push_back(new Sprite(game.renderer,"./Sprites/AllowedSprite.png",curX*64,curY*64,64,64));
        else
            TileEffects.push_back(new Sprite(game.renderer,"./Sprites/AttackSprite.png",curX*64,curY*64,64,64));
    }
}
void GameController::clearOperations(std::vector<operation*>& op) {
    for(std::vector<operation*>::iterator it = op.begin(); it != op.end(); it++)
        delete (*it);
    op.clear();
}
void GameController::ChoosePiece(Init& game,Piece* piece) {
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

bool GameController::validMove(int gotoX,int gotoY) {
    for(std::vector<Sprite*>::iterator it = TileEffects.begin(); it != TileEffects.end(); it++) {
        if(gotoX == (*it)->getX() && gotoY == (*it)->getY())
            return true;
    }
    return false;
}
void GameController::killPiece(Init& game,Piece* piece) {
    piece->isDead = true;
    alivePieces--;
    if(piece->pieceColor == PIECE_COLOR::BLACK) {
        piece->getImg()->setPosition(8 + (game.deadBlack%4),game.deadBlack/4);
        game.deadBlack++;
    } else {
        piece->getImg()->setPosition(8 + (game.deadWhite%4),7-game.deadWhite/4);
        game.deadWhite++;
    }
}
void GameController::unkillPiece(Init& game,Piece* piece,int oldX,int oldY) {
    piece->isDead = false;
    alivePieces++;
    if(piece->pieceColor == PIECE_COLOR::BLACK) {
        piece->getImg()->setPosition(oldX,oldY);
        game.deadBlack--;
    } else {
        piece->getImg()->setPosition(oldX,oldY);
        game.deadWhite--;
    }
}
bool GameController::check(Init& game,int kingColor) {
    int kingX,kingY;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin(); it != game.getPieces().end(); it++) {
        if((*it)->pieceColor == kingColor && (*it)->PieceType == PIECE_TYPE::KING) {
            kingX = (*it)->getImg()->getX();
            kingY = (*it)->getImg()->getY();
            break;
        }
    }
    std::vector<std::pair<int,int> > PossiblePositions;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin(); it != game.getPieces().end(); it++) {
        if((*it)->pieceColor != kingColor && !(*it)->isDead)
            addTilesPerPiece(game,(*it),PossiblePositions);
    }
    for(std::vector<std::pair<int,int> >::iterator it = PossiblePositions.begin(); it != PossiblePositions.end(); it++) {
        if(kingX == (*it).first && kingY == (*it).second)
            return true;
    }
    return false;
}
bool GameController::checkMate(Init& game,int kingColor) {
    if(!check(game,kingColor))
        return false;
    bool ret = true;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin(); it != game.getPieces().end() && ret; it++) {
        if((*it)->pieceColor == kingColor && !(*it)->isDead) {
            std::vector<std::pair<int,int> > PossiblePositions;
            addTilesPerPiece(game,(*it),PossiblePositions);
            for(int j = 0; j < PossiblePositions.size() && ret; j++) {
                int oldX = (*it)->getImg()->getX();
                int oldY = (*it)->getImg()->getY();
                Piece* tmp = game.Board[PossiblePositions[j].first][PossiblePositions[j].second];
                game.Board[PossiblePositions[j].first][PossiblePositions[j].second] = (*it);
                game.Board[oldX][oldY] = NULL;
                (*it)->getImg()->setPosition(PossiblePositions[j].first,PossiblePositions[j].second);
                if(tmp)
                    tmp->isDead = true;
                if(!check(game,kingColor))
                    ret = false;
                game.Board[oldX][oldY] = game.Board[PossiblePositions[j].first][PossiblePositions[j].second];
                game.Board[PossiblePositions[j].first][PossiblePositions[j].second] = tmp;
                (*it)->getImg()->setPosition(oldX,oldY);
                if(tmp)
                    tmp->isDead = false;
            }
        }
    }
    return ret;
}
bool GameController::staleMate(Init& game,int kingColor) {
    bool ret = true;
    for(std::vector<Piece*>::iterator it = game.getPieces().begin(); it != game.getPieces().end() && ret; it++) {
        if((*it)->pieceColor == kingColor && !(*it)->isDead) {
            std::vector<std::pair<int,int> > PossiblePositions;
            addTilesPerPiece(game,(*it),PossiblePositions);
            for(int j = 0; j < PossiblePositions.size() && ret; j++) {
                int oldX = (*it)->getImg()->getX();
                int oldY = (*it)->getImg()->getY();
                Piece* tmp = game.Board[PossiblePositions[j].first][PossiblePositions[j].second];
                game.Board[PossiblePositions[j].first][PossiblePositions[j].second] = (*it);
                game.Board[oldX][oldY] = NULL;
                (*it)->getImg()->setPosition(PossiblePositions[j].first,PossiblePositions[j].second);
                if(tmp)
                    tmp->isDead = true;
                if(!check(game,kingColor))
                    ret = false;
                game.Board[oldX][oldY] = game.Board[PossiblePositions[j].first][PossiblePositions[j].second];
                game.Board[PossiblePositions[j].first][PossiblePositions[j].second] = tmp;
                (*it)->getImg()->setPosition(oldX,oldY);
                if(tmp)
                    tmp->isDead = false;
            }
        }
    }
    return ret;
}
bool GameController::promotePiece(Init& game,Piece* piece,SDL_Keycode buttonClicked) {
    operation* tmp;
    if(buttonClicked == SDLK_0) {
        piece->getImg()->setCropDetails(64*2,piece->pieceColor*64,64,64);
        piece->PieceType = PIECE_TYPE::ROOK;
        tmp = new operation();
        tmp->setOp(piece,NULL,PIECE_TYPE::ROOK,piece->pieceColor,-1,-1,true);
        undoMove.push_back(tmp);
        return true;
    }
    if(buttonClicked == SDLK_1) {
        piece->getImg()->setCropDetails(64*3,piece->pieceColor*64,64,64);
        piece->PieceType = PIECE_TYPE::KNIGHT;
        tmp = new operation();
        tmp->setOp(piece,NULL,PIECE_TYPE::KNIGHT,piece->pieceColor,-1,-1,true);
        undoMove.push_back(tmp);
        return true;
    }
    if(buttonClicked == SDLK_2) {
        piece->getImg()->setCropDetails(64*4,piece->pieceColor*64,64,64);
        piece->PieceType = PIECE_TYPE::BISHOP;
        tmp = new operation();
        tmp->setOp(piece,NULL,PIECE_TYPE::BISHOP,piece->pieceColor,-1,-1,true);
        undoMove.push_back(tmp);
        return true;
    }
    if(buttonClicked == SDLK_3) {
        piece->getImg()->setCropDetails(64,piece->pieceColor*64,64,64);
        piece->PieceType = PIECE_TYPE::QUEEN;
        tmp = new operation();
        tmp->setOp(piece,NULL,PIECE_TYPE::QUEEN,piece->pieceColor,-1,-1,true);
        undoMove.push_back(tmp);
        return true;
    }
    return false;
}
int GameController::getBoardScore(int oldX,int oldY,int newX,int newY) {
    int z = 0;
    if(newY >= 2 && newY <= 5)
        z++;
    if(newY < 2 || newY > 5)
        z--;
    return z;
}
//1 for Player King,2 for AI King
int GameController::getNextMove(Init& game,int depth,bool curTurn,int maxDepth) {
    if(depth == maxDepth)
        return 0;
    int bestValue = (curTurn == PIECE_COLOR::WHITE ? INT_MIN : INT_MAX);
    for(std::vector<Piece*>::iterator it = game.getPieces().begin(); it != game.getPieces().end(); it++) {
        Piece *tmpPiece = (*it);
        if(tmpPiece->isDead || tmpPiece->getImg()->getX() >= 8 || curTurn != tmpPiece->pieceColor)
            continue;
        std::vector<std::pair<int,int> > PossiblePositions;
        addTilesPerPiece(game,tmpPiece,PossiblePositions);
        int oldX = tmpPiece->getImg()->getX();
        int oldY = tmpPiece->getImg()->getY();
        for(int j = 0; j < PossiblePositions.size(); j++) {
            int playValue = 0;
            Piece* target = game.Board[PossiblePositions[j].first][PossiblePositions[j].second];
            game.Board[PossiblePositions[j].first][PossiblePositions[j].second] = (*it);
            game.Board[oldX][oldY] = NULL;
            tmpPiece->getImg()->setPosition(PossiblePositions[j].first,PossiblePositions[j].second);
            if(target) {
                target->isDead = true;
                if(PIECE_COLOR::BLACK == curTurn)
                    playValue -= target->getPieceValue();
                else
                    playValue += target->getPieceValue();
            }
            bool promoted = false;
            if(PossiblePositions[j].first == 7 && curTurn == PIECE_COLOR::WHITE && tmpPiece->PieceType == PIECE_TYPE::PAWN)
                tmpPiece->PieceType = PIECE_TYPE::QUEEN,promoted = true,playValue += 8;
            if(PossiblePositions[j].first == 0 && curTurn == PIECE_COLOR::BLACK && tmpPiece->pieceColor == PIECE_TYPE::PAWN)
                tmpPiece->PieceType = PIECE_TYPE::QUEEN,promoted = true,playValue -= 8;
            if(curTurn == PIECE_COLOR::WHITE) {
                playValue += getNextMove(game,depth + 1,1 - curTurn,maxDepth);
                if(playValue >= bestValue && depth == 0 && !check(game,curTurn)) {
                    game.mouseX = PossiblePositions[j].first*64;
                    game.mouseY = PossiblePositions[j].second*64;
                    lastChoosenPiece = tmpPiece;
                }
                bestValue = std::max(bestValue,playValue);
            } else
                bestValue = std::min(bestValue,playValue + getNextMove(game,depth + 1,1 - curTurn,maxDepth));
            game.Board[oldX][oldY] = game.Board[PossiblePositions[j].first][PossiblePositions[j].second];
            game.Board[PossiblePositions[j].first][PossiblePositions[j].second] = target;
            tmpPiece->getImg()->setPosition(oldX,oldY);
            if(promoted)
                tmpPiece->PieceType = PIECE_TYPE::PAWN;
            if(target)
                target->isDead = false;
        }
    }
    return bestValue;
}
void GameController::undo(Init& game) {
    if(undoMove.size() <= 0)
        return;
    operation* tmp = undoMove.back();
    undoMove.pop_back();
    redoMove.push_back(tmp);
    if(!tmp->promotion) {
        tmp->attacker->getImg()->setPosition(tmp->fromX,tmp->fromY);
        game.Board[tmp->fromX][tmp->fromY] = tmp->attacker;
        if(tmp->attacked) {
            tmp->attacked->isDead = false;
            if(tmp->attacked->pieceColor == PIECE_COLOR::BLACK)
                game.deadBlack--;
            else
                game.deadWhite--;
            tmp->attacked->getImg()->setPosition(tmp->toX,tmp->toY);
            game.Board[tmp->toX][tmp->toY] = tmp->attacked;
        } else game.Board[tmp->toX][tmp->toY] = NULL;
        turn = !turn;
        lastChoosenPiece = NULL;
        ClearTileEffects(TileEffects);
    } else {
        tmp->attacker->PieceType = PIECE_TYPE::PAWN;
        tmp->attacker->getImg()->setCropDetails(64*5,tmp->attacker->pieceColor*64,64,64);
        undo(game);
    }
    return;
}
void GameController::redo(Init& game) {
    if(redoMove.size() <= 0)
        return;
    operation* tmp = redoMove.back();
    redoMove.pop_back();
    undoMove.push_back(tmp);
    if(!tmp->promotion) {
        tmp->attacker->getImg()->setPosition(tmp->toX,tmp->toY);
        game.Board[tmp->toX][tmp->toY] = tmp->attacker;
        game.Board[tmp->fromX][tmp->fromY] = NULL;
        if(tmp->attacked)
            killPiece(game,tmp->attacked);
        turn = !turn;
        lastChoosenPiece = NULL;
        ClearTileEffects(TileEffects);
        if(redoMove.size() && redoMove.back()->promotion)
            redo(game);
    } else {
        tmp->attacker->PieceType = tmp->fromX;
        tmp->attacker->getImg()->setCropDetails(game.TypeToX(tmp->fromX),tmp->attacker->pieceColor*64,64,64);
    }
    return;
}
void GameController::MovePiece(Init& game) {
    int MoveX = (game.mouseX/64);
    int MoveY = (game.mouseY/64);
    if(!validMove(MoveX,MoveY))
        return;
    int lastX = lastChoosenPiece->getImg()->getX();
    int lastY = lastChoosenPiece->getImg()->getY();
    Piece* curPiece = game.Board[MoveX][MoveY];
    lastChoosenPiece->getImg()->setPosition(MoveX,MoveY);
    game.Board[MoveX][MoveY] = game.Board[lastX][lastY];
    game.Board[lastX][lastY] = NULL;
    if(curPiece)
        killPiece(game,curPiece);
    if(check(game,turn)) {
        lastChoosenPiece->getImg()->setPosition(lastX,lastY);
        if(curPiece)
            unkillPiece(game,curPiece,MoveX,MoveY);
        invalidMoveCounter = 80;
        game.Board[lastX][lastY] = lastChoosenPiece;
        game.Board[MoveX][MoveY] = curPiece;
        return;
    }
    operation* newOp = new operation();
    newOp->setOp(lastChoosenPiece,curPiece,lastX,lastY,MoveX,MoveY,false);
    undoMove.push_back(newOp);
    for(std::vector<operation*>::iterator it = redoMove.begin(); it != redoMove.end(); it++)
        delete (*it);
    redoMove.clear();
    if(MoveY == 0 && lastChoosenPiece->pieceColor == PIECE_COLOR::WHITE && lastChoosenPiece->PieceType == PIECE_TYPE::PAWN) {
        if(!isAI)
            SDL_ShowSimpleMessageBox(0,"Promotion!","press 0 for ROOK,1 for Knight,2 for Bishop,3 for Queen",NULL),game.promotionPiece = lastChoosenPiece;
        else {
            lastChoosenPiece->getImg()->setCropDetails(64,lastChoosenPiece->pieceColor*64,64,64);
            lastChoosenPiece->PieceType = PIECE_TYPE::QUEEN;
            operation *tmp = new operation();
            tmp->setOp(lastChoosenPiece,NULL,PIECE_TYPE::QUEEN,lastChoosenPiece->pieceColor,-1,-1,true);
            undoMove.push_back(tmp);
        }
    }
    if(MoveY == 7 && lastChoosenPiece->pieceColor == PIECE_COLOR::BLACK && lastChoosenPiece->PieceType == PIECE_TYPE::PAWN)
        SDL_ShowSimpleMessageBox(0,"Promotion!","press 0 for ROOK,1 for Knight,2 for Bishop,3 for Queen",NULL),game.promotionPiece = lastChoosenPiece;
    turn = !turn;
    lastChoosenPiece = NULL;
    ClearTileEffects(TileEffects);
}

/*
int AiMove(depth,turn)
{
    if(depth = 0)
        return evaluationBoard()

        if(turn)
        {
            curValue = -INF;
            for i = 0,allPossibleMoves do
            {
                if(validMove(i))
                {
                    doMove(i)
                    int nextAi = AiMove(depth - 1,1 - turn)
                    if(nextAi >= curValue)
                        nextMove = i,nextAi = curValue
                    undoMove(i)
                }
            }
            return curValue;
        } else {
            curValue = INF;
            for i = 0,allPossibleMoves do
            {
                if(validMove(i))
                {
                    doMove(i)
                    int nextAi = AiMove(depth - 1,1 - turn)
                    if(nextAi <= curValue)
                        nextAi = curValue
                    undoMove(i)
                }
            }
            return curValue;
        }
    return 0
}
*/

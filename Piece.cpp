#include "Piece.h"

Piece::Piece(bool piece_Color,int Piece_Type)
{
    pieceColor = piece_Color;
    PieceType = Piece_Type;
    isDead = false;
}

Piece::~Piece()
{
    delete PieceImg;
}

int Piece::getPieceValue()
{
    if(PieceType == 0)
        return 5;
    if(PieceType == 1)
        return 3;
    if(PieceType == 2)
        return 3;
    if(PieceType == 3)
        return 9;
    if(PieceType == 4)
        return 3000;
    return 1;
}

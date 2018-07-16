#include "Piece.h"

Piece::Piece(bool piece_Color,int Piece_Type)
{
    pieceColor = piece_Color;
    PieceType = Piece_Type;
}

Piece::~Piece()
{
    delete PieceImg;
}

#include "../Include/Piece.h"

Piece::Piece(bool piece_Color,int Piece_Type) {
    pieceColor = piece_Color;
    PieceType = Piece_Type;
    isDead = false;
}

Piece::~Piece() {
    delete PieceImg;
}

int Piece::getPieceValue() {
    if(PieceType == PIECE_TYPE::ROOK)
        return 5;
    if(PieceType == PIECE_TYPE::KNIGHT)
        return 3;
    if(PieceType == PIECE_TYPE::BISHOP)
        return 3;
    if(PieceType == PIECE_TYPE::QUEEN)
        return 9;
    if(PieceType == PIECE_TYPE::KING)
        return 50;
    return 1;
}

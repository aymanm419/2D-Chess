#ifndef PIECE_H
#define PIECE_H
#include "Sprite.h"

class Piece
{
    public:
        Piece(bool piece_Color,int Piece_Type);
        virtual ~Piece();
        Sprite* getImg() {return PieceImg;}
        Sprite* PieceImg;
        bool pieceColor;
        int PieceType;
    protected:

    private:
};

#endif // PIECE_H

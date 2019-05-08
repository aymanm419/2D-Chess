#ifndef PIECE_H
#define PIECE_H
#include "Sprite.h"
enum PIECE_COLOR {
    BLACK = 0,
    WHITE = 1
};
enum PIECE_TYPE {
    PAWN = 5,
    KING = 4,
    QUEEN = 3,
    BISHOP = 2,
    KNIGHT = 1,
    ROOK = 0
};
class Piece {
public:
    Piece(bool piece_Color,int Piece_Type);
    virtual ~Piece();
    Sprite* getImg() {
        return PieceImg;
    }
    int getPieceValue();
    Sprite* PieceImg;
    bool pieceColor,isDead;
    int PieceType;
protected:

private:
};

#endif // PIECE_H

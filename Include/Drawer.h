#ifndef DRAWER_H
#define DRAWER_H
#include <vector>
#include "Sprite.h"
#include "Init.h"
#include "Piece.h"
class Drawer {
public:
    void Draw(Sprite* curSprite,Init& CurGame);
    void DrawPieces(std::vector<Piece*>& VectorSprite,Init& curGame);
    void DrawSprites(std::vector<Sprite*>& VectorSprite,Init& curGame);
protected:

private:
};

#endif // DRAWER_H

#ifndef SPRITE_H
#define SPRITE_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#define MAX_WINDOWS_WIDTH 512
#define MAX_WINDOWS_HEIGHT 512
class Sprite
{
    public:
        Sprite(SDL_Renderer* renderer,char* FileDir,int x,int y,int w,int h);
        Sprite(const Sprite& sp);
        virtual ~Sprite();
        void SetX(int value);
        void SetY(int value);
        int getX() {return mainRect.x;}
        int getY() {return mainRect.y;}
        void setCropDetails(int cropX,int cropY,int cropW,int cropH);
        void setRectDetails(int x,int y,int w,int h);
        SDL_Rect getMainRect() {return mainRect;}
        SDL_Rect getCropRect() {return cropRect;}
        SDL_Texture* getTexture() const {return curTexture;}
        int32_t img_width,img_height;
    protected:

    private:
        SDL_Texture* curTexture;
        SDL_Rect mainRect;
        SDL_Rect cropRect;
        uint32_t timeSinceLastMove;
};

#endif // Sprite_H
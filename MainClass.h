#ifndef MAINCLASS_H
#define MAINCLASS_H
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#define MAX_WINDOWS_WIDTH 600
#define MAX_WINDOWS_HEIGHT 480
class MainClass
{
    public:
        MainClass(SDL_Renderer* renderer,char* FileDir,int x,int y,int w,int h,int v);
        virtual ~MainClass();
        void Draw(SDL_Renderer* renderer,bool crop = false);
        void SetX(float value);
        void SetY(float value);
        void SetPosition(float X,float Y);
        void SetControls(int KeyMoveType,int clicked,std::vector<int>& MovingKeys,SDL_Renderer* renderer);
        void MoveToMouse();
        float getXPosition() {return X_pos;}
        float getYPosition() {return Y_pos;}
        void setLastMousePosition(int x,int y);
        double getDistance(int X1,int Y1,int X2,int Y2);
        double getSpeed() {return speed;}
        void PlayAnimation(int BeginFrame,int EndFrame,float angle,float speed);
        void SetupAnimation(int AnimationX,int AnimationY,int AnimationSpeed);
        float getAngle();
        bool follow;
    protected:

    private:
        SDL_Texture* curTexture;
        SDL_Rect mainRect;
        SDL_Rect cropRect;
        int MoveDir,Mouse_X_Click,Mouse_Y_Click;
        uint32_t timeSinceLastMove;
        float speed;
        float X_pos,Y_pos;
        int32_t img_height,img_width;
        int currentFrame,animationDelay,Animation_X,Animation_Y,Animation_Speed,lastRow;

};

#endif // MAINCLASS_H

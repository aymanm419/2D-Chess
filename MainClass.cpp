#include "MainClass.h"
#include <vector>
#include <iostream>
#include <cmath>
#define epison 1e-4
#define MATH_PI 3.1415926535897932384626433832795
MainClass::MainClass(SDL_Renderer* renderer,char* FileDir,int x,int y,int w,int h,int v)
{
    curTexture = IMG_LoadTexture(renderer,FileDir);
    SDL_QueryTexture(curTexture,NULL,NULL,&img_width,&img_height);
    mainRect.x = x;
    mainRect.y = y;
    mainRect.w = w;
    mainRect.h = h;
    speed = v;
    timeSinceLastMove = SDL_GetTicks();
    MoveDir = Mouse_X_Click = Mouse_Y_Click = 0;
    follow = false;
    X_pos = x;
    Y_pos = y;
    cropRect.x = 0;
    cropRect.y = 0;
    cropRect.w = img_width/9;
    cropRect.h = img_height/4;
    currentFrame = 0;
    animationDelay = 0;

}
MainClass::~MainClass()
{
    SDL_DestroyTexture(curTexture);
    MoveDir = 0;
    speed = 0;
}
void MainClass::Draw(SDL_Renderer* renderer,bool crop /*= false*/)
{
    if(crop)
        SDL_RenderCopy(renderer,curTexture,&cropRect,&mainRect);
    else
        SDL_RenderCopy(renderer,curTexture,NULL,&mainRect);
}
void MainClass::SetX(float value)
{
    X_pos = value;
    mainRect.x = int(X_pos);
}
void MainClass::SetY(float value)
{
    Y_pos = value;
    mainRect.y = int(Y_pos);
}
void MainClass::SetPosition(float X,float Y)
{
    X_pos = X;
    Y_pos = Y;
    mainRect.x = int(X_pos);
    mainRect.y = int(Y_pos);
}
void MainClass::setLastMousePosition(int x,int y)
{
    Mouse_X_Click = x - (mainRect.w/2);
    Mouse_Y_Click = y - (mainRect.h/2);
    return;
}
float MainClass::getAngle()
{
    float DeltaY = Mouse_Y_Click - getYPosition();
    float DeltaX = Mouse_X_Click - getXPosition();

    float angle = atan2(DeltaY,DeltaX) * 180 / MATH_PI;
    return angle+180;
}
double MainClass::getDistance(int X1,int Y1,int X2,int Y2)
{
    double DifferenceX = (X1 - X2);
    double DifferenceY = (Y1 - Y2);
    double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
    return distance;
}
void MainClass::SetControls(int KeyMoveType,int clicked,std::vector<int>& MovingKeys,SDL_Renderer* renderer)
{
    if(timeSinceLastMove + 5 < SDL_GetTicks())
    {
        if(KeyMoveType == SDL_KEYDOWN)
        {
            for(int i = 0;i < 4;i++)
            {
                if(clicked == MovingKeys[i])
                    MoveDir |= (1 << (i+1));
            }
        }
        if(KeyMoveType == SDL_KEYUP)
        {
            for(int i = 0;i < 4;i++)
            {
                if(clicked == MovingKeys[i])
                    MoveDir &= ~(1 << (i+1));
            }
        }
        if(MoveDir & (1 << 1))
            SetX(getXPosition() - speed),PlayAnimation(0,Animation_X-1,360,Animation_Speed);
        if(MoveDir & (1 << 2))
            SetY(getYPosition() + speed),PlayAnimation(0,Animation_X-1,315,Animation_Speed);
        if(MoveDir & (1 << 3))
            SetX(getXPosition() + speed),PlayAnimation(0,Animation_X-1,225,Animation_Speed);
        if(MoveDir & (1 << 4))
           SetY(getYPosition() - speed),PlayAnimation(0,Animation_X-1,135,Animation_Speed);
        timeSinceLastMove = SDL_GetTicks();
    } else
    {
        if(KeyMoveType == SDL_KEYDOWN)
        {
            for(int i = 0;i < 4;i++)
            {
                if(clicked == MovingKeys[i])
                    MoveDir |= (1 << (i+1));
            }
        }
        if(KeyMoveType == SDL_KEYUP)
        {
            for(int i = 0;i < 4;i++)
            {
                if(clicked == MovingKeys[i])
                    MoveDir &= ~(1 << (i+1));
            }
        }
    }
}
void MainClass::MoveToMouse()
{
    double curDistane = getDistance(getXPosition(),getYPosition(),Mouse_X_Click,Mouse_Y_Click);
    float curAngle = getAngle();
    if(curDistane <= epison)
        follow = false,PlayAnimation(0,0,-1,Animation_Speed);
    if(follow && timeSinceLastMove + 5 < SDL_GetTicks())
    {
        if(getXPosition() < Mouse_X_Click)
            SetX(std::min(getXPosition()-((getXPosition() - Mouse_X_Click) / curDistane) * getSpeed(),1.00*Mouse_X_Click));
        if(getXPosition() > Mouse_X_Click)
            SetX(std::max(getXPosition()-((getXPosition() - Mouse_X_Click) / curDistane) * getSpeed(),1.00*Mouse_X_Click));
        if(getYPosition() < Mouse_Y_Click)
            SetY(std::min(getYPosition()-((getYPosition() - Mouse_Y_Click) / curDistane) * getSpeed(),1.00*Mouse_Y_Click));
        if(getYPosition() > Mouse_Y_Click)
            SetY(std::max(getYPosition()-((getYPosition() - Mouse_Y_Click) / curDistane) * getSpeed(),1.00*Mouse_Y_Click));
        PlayAnimation(0,Animation_X-1,curAngle,Animation_Speed);
        timeSinceLastMove = SDL_GetTicks();
    }
}
void MainClass::SetupAnimation(int AnimationX,int AnimationY,int AnimationSpeed)
{
    Animation_X = AnimationX;
    Animation_Y = AnimationY;
    Animation_Speed = AnimationSpeed;
}
void MainClass::PlayAnimation(int BeginFrame,int EndFrame,float curAngle,float speed)
{
    int Row;
    if(curAngle == -1)
    {
        cropRect.x = 0;
        cropRect.y = lastRow * (img_height/Animation_Y);
        cropRect.w = img_width / Animation_X;
        cropRect.h = img_height / Animation_Y;
        return;
    }
    if(animationDelay+speed < SDL_GetTicks())
    {
        if(currentFrame+1 <= EndFrame)
            currentFrame++;
        else
            currentFrame = 0;
        if(curAngle > 45 && curAngle <= 135)
            Row = 0;
        else if(curAngle > 135 && curAngle <= 225)
            Row = 3;
        else if(curAngle > 225 && curAngle <= 315)
            Row = 2;
        else
            Row = 1;
        cropRect.x = currentFrame * (img_width/Animation_X);
        cropRect.y = Row * (img_height/Animation_Y);
        cropRect.w = img_width / Animation_X;
        cropRect.h = img_height / Animation_Y;
        animationDelay = SDL_GetTicks();
        lastRow = Row;
    }
}



#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "MainClass.h"
#include "Init.h"
#include <vector>
uint32_t curTime;
int32_t mouseX,mouseY;
std::vector<int> ControlSet1;
std::vector<int> ControlSet2;
char* backgroundImg = "download.png";
char* mainCharacterImg = "prof.png";
void Initalize()
{
    ControlSet1.push_back(SDLK_a);
    ControlSet1.push_back(SDLK_s);
    ControlSet1.push_back(SDLK_d);
    ControlSet1.push_back(SDLK_w);
    ControlSet2.push_back(SDLK_LEFT);
    ControlSet2.push_back(SDLK_DOWN);
    ControlSet2.push_back(SDLK_RIGHT);
    ControlSet2.push_back(SDLK_UP);
}
int main( int argc, char * argv[] )
{
    Initalize();
    Init Game;
    MainClass curGrass(Game.renderer,backgroundImg,0,0,MAX_WINDOWS_WIDTH,MAX_WINDOWS_HEIGHT,0);
    MainClass Bob(Game.renderer,mainCharacterImg,MAX_WINDOWS_WIDTH/2,MAX_WINDOWS_HEIGHT/2,125,125,1.5f);
    Bob.SetupAnimation(9,4,125);
    curTime = SDL_GetTicks();
    while(!Game.quit && Game.mainEvent->type != SDL_QUIT)
    {
        Game.Begin();
        curGrass.Draw(Game.renderer);
        //Bob.SetControls(Game.mainEvent->type,Game.mainEvent->key.keysym.sym,ControlSet1,Game.renderer);
        if(Game.mainEvent->type == SDL_MOUSEBUTTONDOWN && Game.mainEvent->button.button == SDL_BUTTON_LEFT){
            SDL_GetMouseState(&mouseX,&mouseY);
            Bob.follow = true;
            Bob.setLastMousePosition(mouseX,mouseY);
        }
        Bob.MoveToMouse();
        Bob.Draw(Game.renderer,true);
        Game.End();
    }
    Game.~Init();
    curGrass.~MainClass();
    Bob.~MainClass();
    return 1;
}

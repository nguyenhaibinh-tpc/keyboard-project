//
// Created by pc on 11/3/2021.
//

#ifndef MAIN_CPP_OBJECT_H
#define MAIN_CPP_OBJECT_H


#include <vector>
#include <string>
#include "SDL2/SDL.h"

class Timer{

};
class Object{
public:

    void UpDown(int delay, int UpDis, int DownDis,bool UpFirst);
    void Left(int delay);
    void Right(int delay);
    void SetDestR(int x, int y, int w, int h);
    void SetSrcR(int x, int y, int w, int h);
    void Wait(int delay);
    bool isWaiting();

    SDL_Rect srcR;
    SDL_Rect destR;
    Uint32 lastMovedTimeX = 0;
    Uint32 lastMovedTimeY = 0;

    Uint32 WaitTime = 0;
    Uint32 lastWaitTime = 0;


    int UpMoved = 0;
    int DownMoved = 0;
};
class Textures : public Object{
public:

    Textures();
    Textures(int type, std::string location);
    void SetTexture(SDL_Texture *texture);
    void Render(int state = 0);

    void RenderAnimation();
    void UpdateAnimation();
    void SetAnimation(std::vector<SDL_Texture *> animation);
    void SetAnimationDelay(Uint32 delay);

    // animation
    Uint32 animationDelay;
    Uint32 lastAnimationTime = 0;
    int currentAnimation = 0;

    //texture container
    std::vector<SDL_Texture *> animation;
    SDL_Texture *texture;

    // indicator
    Button(bool active);
    Uint32 lastUsedTime;
    bool isActive;
    bool isClicked;
};

class Word: public Object{
public:
    Word(std::string word);
    void HandleEvent(SDL_Event event);
    void Update();
    void RenderWord();
    bool Complete() ;

    std::vector<SDL_Texture *> wordTexture;
    int color, typed;
    bool isGone = 0;
    std::string word = "";
    Uint32 lastMovedTime = 0;
};

class Enemy{
public:
    Enemy(int enemyType);
    ~Enemy();
    bool Disappear();
    void StateUpdate();
    void FrameUpdate();
    void Render();
    void WordFollow();
    void HandleEvent(SDL_Event event);
    Word* word;

    int enemyType;
    int health;
    int damage;
    int state;
    int stateLocal;
    int wordCnt;

    Textures frameCycle;
    Textures frameCycle2;

    int randVar1;
    int randVar2;
    int randVar3;
};




#endif //MAIN_CPP_OBJECT_H

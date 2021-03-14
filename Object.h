//
// Created by pc on 11/3/2021.
//

#ifndef MAIN_CPP_OBJECT_H
#define MAIN_CPP_OBJECT_H


#include <vector>
#include <string>
#include "SDL2/SDL.h"


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
class Animation : public Object{
public:
    void RenderAnimation();
    void UpdateAnimation();
    void SetAnimation(std::vector<SDL_Texture *> animation);
    void SetAnimationDelay(Uint32 delay);

    std::vector<SDL_Texture *> animation;
    SDL_Texture *objTexture;

    Uint32 animationDelay;
    Uint32 lastAnimationTime = 0;
    int currentAnimation = 0;
};
class StillFrame : public Object{
public:
    void SetTexture(SDL_Texture *texture);
    void Render(int state = 0);

    SDL_Texture *texture;

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
    int enemyType;
    int health;
    int damage;
    bool isDead = 0;
    bool isDamaged = 0;

    Enemy(int enemyType);
    ~Enemy();
    void Check();
    void Update();
    void Render();
    void WordFollow();
    void HandleEvent(SDL_Event event);
    Word* word;

    int randVar1;
    int randVar2;
    int randVar3;

    int state;
    int wordCnt;

    Animation frameCycle;
    Animation frameCycle2;
};




#endif //MAIN_CPP_OBJECT_H

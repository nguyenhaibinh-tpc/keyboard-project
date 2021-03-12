//
// Created by pc on 10/3/2021.
//

#ifndef MAIN_CPP_ANIMATEDOBJECT_H
#define MAIN_CPP_ANIMATEDOBJECT_H


#include <vector>
#include "SDL2/SDL.h"

class AnimatedObject {
public:

    void Render();
    void Update();
    void SetAnimation(std::vector<SDL_Texture *> animation);
    void SetDestR(int x, int y, int w, int h);
    void SetSrcR(int x, int y, int w, int h);
    void SetAnimationDelay(Uint32 delay);

    std::vector<SDL_Texture *> animation;
    SDL_Texture *objTexture;
    SDL_Rect srcR;
    SDL_Rect destR;

    Uint32 animationDelay;
    Uint32 lastAnimationTime = 0;
    int currentAnimation = 0;
};


#endif //MAIN_CPP_ANIMATEDOBJECT_H

//
// Created by pc on 10/3/2021.
//

#include "AnimatedObject.h"
#include "Manager.h"

void AnimatedObject::SetAnimation(std::vector<SDL_Texture *> animation) {
    AnimatedObject::animation = animation;
}

void AnimatedObject::Render() {
    SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
}

void AnimatedObject::Update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime >= lastAnimationTime + animationDelay) {
        objTexture = animation[currentAnimation];
        currentAnimation = (currentAnimation + 1) % animation.size();
        lastAnimationTime = currentTime;
    }
}

void AnimatedObject::SetAnimationDelay(Uint32 delay) {
    animationDelay = delay;
}

void AnimatedObject::SetDestR(int x, int y, int w, int h) {
    destR.x = x;
    destR.y = y;
    destR.w = w;
    destR.h = h;
}

void AnimatedObject::SetSrcR(int x, int y, int w, int h) {
    srcR.x = x;
    srcR.y = y;
    srcR.w = w;
    srcR.h = h;
}
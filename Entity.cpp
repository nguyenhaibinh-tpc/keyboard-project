//
// Created by pc on 11/3/2021.
//

#include <vector>
#include <iostream>
#include "Entity.h"
#include "TextureLoader.h"
#include "Manager.h"

std::vector<SDL_KeyCode> typeList = {
        SDLK_a,
        SDLK_b,
        SDLK_c,
        SDLK_d,
        SDLK_e,
        SDLK_f,
        SDLK_g,
        SDLK_h,
        SDLK_i,
        SDLK_j,
        SDLK_k,
        SDLK_l,
        SDLK_m,
        SDLK_n,
        SDLK_o,
        SDLK_p,
        SDLK_q,
        SDLK_r,
        SDLK_s,
        SDLK_t,
        SDLK_u,
        SDLK_v,
        SDLK_w,
        SDLK_x,
        SDLK_y,
        SDLK_z
};

void Entity::Update() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime >= lastMovedTime + 8) {
        destR.x--;
        objTexture = animation[currentAnimation];
        lastMovedTime = currentTime;
    }
    if (currentTime >= lastAnimationTime + animationDelay) {
        currentAnimation = (currentAnimation + 1) % animation.size();
        lastAnimationTime = currentTime;
    }
}

Entity::Entity(std::string word) {
    wordTexture.clear();
    Entity::word = word;
    color = rand() % 6 + 1;
    for (auto i:word) {
        wordTexture.emplace_back();
        std::string go = "";
        go += i;
        wordTexture.back() = TextureLoader::LoadText(go, 24, 0);
    }
    destR.x = 1000;
    destR.y = rand() % 400 + 100;
    destR.w = 20;
    destR.h = 24;
    typed = 0;
}

void Entity::handleEvent(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            if (typed < word.size() && event.key.keysym.sym == typeList[word[typed] - 'a']) {
                std::string go = "";
                go += Entity::word[typed];
                wordTexture[typed] = TextureLoader::LoadText(go, 24, color);
                typed++;
            }
            break;
        default:
            break;
    }
}

void Entity::Render() {
    auto tmpR = destR;
    for (int i = 0; i < wordTexture.size(); ++i) {
        tmpR.x += 20;
        SDL_RenderCopy(Manager::renderer, wordTexture[i], nullptr, &tmpR);
    }
    tmpR = destR;
    tmpR.y += 15;
    tmpR.x = destR.x + 20 * word.size() / 2 - 100 / 2 + 10;
    tmpR.h = tmpR.w = 120;
    SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &tmpR);
}
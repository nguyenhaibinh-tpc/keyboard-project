//
// Created by pc on 11/3/2021.
//

#ifndef MAIN_CPP_ENTITY_H
#define MAIN_CPP_ENTITY_H


#include <string>
#include "SDL2/SDL.h"
#include "AnimatedObject.h"

class Entity : public AnimatedObject {
public:
    Entity(std::string word);
    void handleEvent(SDL_Event event);
    void Update();
    void Render();

    std::string word = "";
    int typed = 0;
    int color = 0;
    std::vector<SDL_Texture *> wordTexture;
    SDL_Rect destR = {0, 0, 0, 0};

    Uint32 lastMovedTime = 0;
};


#endif //MAIN_CPP_ENTITY_H

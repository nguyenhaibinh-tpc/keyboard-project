//
// Created by pc on 10/3/2021.
//

#ifndef MAIN_CPP_BUTTON_H
#define MAIN_CPP_BUTTON_H

#include "SDL2/SDL.h"

class Button {
public:
    Button(bool active = true);
    void SetTexture(SDL_Texture *texture);
    void HandleEvents(SDL_Event event);
    void Render();
    void SetSrcR(int x,int y,int w,int h);
    void SetDestR(int x,int y,int w,int h);

    Uint32 lastUsedTime;
    bool isActive;
    bool isClicked;
    SDL_Texture *texture;
    SDL_Rect srcR;
    SDL_Rect destR;
};


#endif //MAIN_CPP_BUTTON_H

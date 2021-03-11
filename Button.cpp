//
// Created by pc on 10/3/2021.
//

#include "Button.h"
#include "Manager.h"

void Button::SetTexture(SDL_Texture *texture) {
    Button::texture = texture;
}

void Button::HandleEvents(SDL_Event event) {
    isClicked = false;
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            int xpos, ypos;
            SDL_GetMouseState(&xpos, &ypos);
            if (destR.x <= xpos && xpos <= destR.x + destR.w &&
                destR.y <= ypos && ypos <= destR.y + destR.h) {
                isClicked = true;
            }
            break;
        default:
            break;
    }
}

void Button::Render(int state) {
    state ? SDL_RenderCopy(Manager::renderer, texture, &srcR, &destR) :
    SDL_RenderCopy(Manager::renderer, texture, nullptr, &destR);
}

Button::Button(bool active) {
    isActive = active;
    isClicked = false;
    lastUsedTime = 0;
}

void Button::SetSrcR(int x, int y, int w, int h) {
    Button::srcR.x = x;
    Button::srcR.y = y;
    Button::srcR.w = w;
    Button::srcR.h = h;
}

void Button::SetDestR(int x, int y, int w, int h) {
    Button::destR.x = x;
    Button::destR.y = y;
    Button::destR.w = w;
    Button::destR.h = h;
}

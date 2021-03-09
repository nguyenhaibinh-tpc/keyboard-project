//
// Created by pc on 09/3/2021.
//

#ifndef KEYBOARD_PROJECT_MANAGER_H
#define KEYBOARD_PROJECT_MANAGER_H

#include "SDL2/SDL.h"

class Manager {
public:
    Manager();
    ~Manager();

    void Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};

#endif //KEYBOARD_PROJECT_MANAGER_H

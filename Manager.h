//
// Created by pc on 09/3/2021.
//

#ifndef KEYBOARD_PROJECT_MANAGER_H
#define KEYBOARD_PROJECT_MANAGER_H

#include "SDL2/SDL.h"
#include "Button.h"
#include "AnimatedObject.h"

class Manager {
public:
    Manager();

    ~Manager();

    void Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen);

    void HandleGameEvents();
    void UpdateGame();
    void RenderGame();

    void InitMenu();
    void HandleMenuEvents();
    void UpdateMenu();
    void RenderMenu();

    void Clean();

    static SDL_Renderer *renderer;

//private:
    bool isRunning;
    bool isAtMenu;
    SDL_Window *window;

    Button *testButton;
    Button *gameLogo;
    AnimatedObject *menuBackground;

public:
    bool GetIsRunning() {
        return isRunning;
    }

    bool GetIsAtMenu() {
        return isAtMenu;
    }
};

#endif //KEYBOARD_PROJECT_MANAGER_H

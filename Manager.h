//
// Created by pc on 09/3/2021.
//

#ifndef KEYBOARD_PROJECT_MANAGER_H
#define KEYBOARD_PROJECT_MANAGER_H

#include "SDL2/SDL.h"
#include "Button.h"
#include "AnimatedObject.h"
#include "string"
#include "Entity.h"

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

    void InitDictionary();

    static SDL_Renderer *renderer;

//private:
    bool isRunning;
    bool isAtMenu;
    SDL_Window *window;

    Button *testButton;
    Button *gameLogo;
    Button *startButton;
    Button *optionsButton;
    Button *exitButton;
    Button *handPointer;

    int handPointerPos = 0;

    AnimatedObject *menuBackground;

    std::vector<std::string> dictionary;
    std::vector<std::string> effortlessWords;
    std::vector<std::string> easyWords;
    std::vector<std::string> normalWords;
    std::vector<std::string> hardWords;
    std::vector<std::string> extremeWords;
    std::vector<Entity *> enemies;

public:
    bool GetIsRunning() {
        return isRunning;
    }

    bool GetIsAtMenu() {
        return isAtMenu;
    }
};

#endif //KEYBOARD_PROJECT_MANAGER_H

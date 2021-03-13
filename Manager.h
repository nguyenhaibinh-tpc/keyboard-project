//
// Created by pc on 09/3/2021.
//

#ifndef KEYBOARD_PROJECT_MANAGER_H
#define KEYBOARD_PROJECT_MANAGER_H

#include "SDL2/SDL.h"
#include "string"
#include "Object.h"


enum enemyType{enemyBird, enemyBat, enemyKnight};

const int WINDOWSIZEW = 1000;
const int WINDOWSIZEH = 600;
const int MIDDLESCREEN = 300;
const int PLAYERX = 100;

int rnd(int l, int r);

//extern int playerHealth = 100;
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

    StillFrame *testButton;
    StillFrame *gameLogo;
    StillFrame *startButton;
    StillFrame *optionsButton;
    StillFrame *exitButton;
    StillFrame *handPointer;

    int handPointerPos = 0;

    Animation *menuBackground;
    StillFrame *gameBackground;

    std::vector<std::string> dictionary;
    std::vector<std::string> effortlessWords;
    std::vector<std::string> easyWords;
    std::vector<std::string> normalWords;
    std::vector<std::string> hardWords;
    std::vector<std::string> extremeWords;

    std::vector<Word *> words;
    std::vector<Enemy *> enemies;

    static int playerHealth;
    static int debug1 ;
    static int debug2 ;
    Uint32 lastSpawnTime = 0;

    bool GetIsRunning() {
        return isRunning;
    }

    bool GetIsAtMenu() {
        return isAtMenu;
    }

    std::string newWord();
};

#endif //KEYBOARD_PROJECT_MANAGER_H

//
// Created by pc on 09/3/2021.
//

#ifndef KEYBOARD_PROJECT_MANAGER_H
#define KEYBOARD_PROJECT_MANAGER_H


#include "SDL2/SDL.h"
#include "string"
#include "Object.h"

enum enemyType{
    enemyBird,
    enemyBat,
    enemyKnight
};
enum stateEnemy{
    isDead,
    isAlive,
};
enum stateEnemyLocal{
    knightIdle,
    knightRunning
};

enum gameState{
    gameMenu,
    gamePlaying,
    gameEnded
};

const int WINDOWSIZEW = 1000;
const int WINDOWSIZEH = 600;
const int MIDDLESCREEN = 300;
const int PLAYERX = 0;

int rnd(int l, int r);

class Manager {
public:
    Manager();

    ~Manager();

    void Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen);
    void HandleGameEvents();
    void UpdateGame();
    void RenderGame();
    void InitTexture();
    void HandleMenuEvents();
    void UpdateMenu();
    void RenderMenu();
    void HandleEndedEvents();
    void UpdateEnded();
    void RenderEnded();
    void CleanGame();
    void Clean();

    static SDL_Renderer *renderer;


//private:
    bool isRunning;
    int gameState;
    SDL_Window *window;

    Textures *testButton;
    Textures *gameLogo;
    Textures *startButton;
    Textures *optionsButton;
    Textures *exitButton;
    Textures *handPointer;
    Textures *gameOver;

    int handPointerPos = 0;

    Textures *menuBackground;
    Textures *gameBackgroundSky;
    Textures *gameBackgroundLand;

    std::vector<Enemy *> enemies;

    static int playerHealth;
    static int debug1;
    static int debug2;
    Uint32 lastSpawnTime = 0;

};

extern Manager *game;
#endif //KEYBOARD_PROJECT_MANAGER_H

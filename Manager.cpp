//
// Created by pc on 09/3/2021.
//

#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <limits.h>
#include "Manager.h"
#include "TextureLoader.h"
#include "Dictionary.h"


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) { return l + rng() % (r - l + 1); }

SDL_Renderer *Manager::renderer = nullptr;
int Manager::playerHealth;
int Manager::debug1 = 0;
int Manager::debug2 = 0;


Manager::Manager() {
    TTF_Init();
    isRunning = true;
    gameState = gameMenu;
    playerHealth = INT_MAX;
}

void Manager::InitTexture() {
    gameLogo = new Textures(0, "../resources/game-logo.png");
    gameLogo->SetDestR(300, -50, 400, 400);

    menuBackground = new Textures(1, "menu-background-");
    menuBackground->SetAnimationDelay(120);
    menuBackground->SetDestR(0, 0, WINDOWSIZEW, WINDOWSIZEH);

    gameBackgroundSky = new Textures(0, "../resources/game-background-sky.png");
    gameBackgroundSky->SetDestR(0, 0, WINDOWSIZEW * 2, WINDOWSIZEH);

    gameBackgroundLand = new Textures(0, "../resources/game-background-land.png");
    gameBackgroundLand->SetDestR(0, 13, WINDOWSIZEW, 587);

    startButton = new Textures(0, "../resources/menu-button.png");
    startButton->SetSrcR(0, 0, 625, 125);
    startButton->SetDestR(422, 100 + 250, 156, 31);

    optionsButton = new Textures(0, "../resources/menu-button.png");
    optionsButton->SetSrcR(0, 125, 625, 162);
    optionsButton->SetDestR(422, 140 + 250, 156, 40);

    exitButton = new Textures(0, "../resources/menu-button.png");
    exitButton->SetSrcR(0, 287, 625, 125);
    exitButton->SetDestR(422, 180 + 250, 156, 31);

    handPointer = new Textures(0, "../resources/hand-pointer.png");
    //handPointer->SetTexture(TextureLoader::LoadText("lozchinese",25,0));
    handPointer->SetDestR(590, 355, 30, 25);

    gameOver = new Textures(0, "../resources/game-over.png");
    //handPointer->SetTexture(TextureLoader::LoadText("lozchinese",25,0));
    gameOver->SetDestR(0, 0, WINDOWSIZEW, WINDOWSIZEH);
}

void Manager::Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int isFullScreen = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, isFullScreen);
        Manager::renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(Manager::renderer, 255, 255, 255, 255);
    } else {
        std::cout << "Failed to load SDL!\n";
        exit(0);
    }
}

void Manager::HandleMenuEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    (handPointerPos += 2) %= 3;
                    break;
                case SDLK_DOWN:
                    (handPointerPos += 1) %= 3;
                    break;
                case SDLK_RETURN:
                    switch (handPointerPos) {
                        case 0:
                            gameState = gamePlaying;
                            break;
                        case 1:
                            break;
                        case 2:
                            isRunning = false;
                            break;
                    }
                    break;
            }
        default:
            break;
    }
}

int dir = 1;

void Manager::UpdateMenu() {
    Uint32 currentTime = SDL_GetTicks();
    if (gameLogo->destR.y == 10)
        dir = -1;
    if (gameLogo->destR.y == -50)
        dir = 1;
    if (currentTime >= gameLogo->lastUsedTime + 40) {
        gameLogo->destR.y += dir;
        gameLogo->lastUsedTime = currentTime;
    }
    handPointer->destR.y = handPointerPos * 40 + 355;
    menuBackground->UpdateAnimation();


}

void Manager::RenderMenu() {
    SDL_RenderClear(renderer);
    menuBackground->RenderAnimation();
    gameLogo->Render();
    startButton->Render(1);
    optionsButton->Render(1);
    exitButton->Render(1);
    handPointer->Render();
    SDL_RenderPresent(renderer);
}


void Manager::HandleGameEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    debug1++;
                    break;
                case SDLK_DOWN:
                    debug1--;
                    break;
                case SDLK_LEFT:
                    debug2--;
                    break;
                case SDLK_RIGHT:
                    debug2++;
                    break;
            }
        default:
            break;
    }
    for (auto enemy:enemies)
        enemy->word->HandleEvent(event);

}

void Manager::CleanGame() {
    gameState = gameMenu;
    playerHealth = 50;
    enemies.clear();
}

void Manager::UpdateGame() {
    // background
    gameBackgroundSky->Left(50);
    if (gameBackgroundSky->destR.x + WINDOWSIZEW == 0) {
        gameBackgroundSky->destR.x = 0;
    }

    //spawning monster
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime >= lastSpawnTime + 1500 && enemies.size() >= 0 || !rnd(0,2000)) {

        enemies.emplace_back();

        int random = rnd(0, 2);
        enemies.back() = new Enemy(random);
        //enemies.back() = new Enemy(enemyBat);

        lastSpawnTime = currentTime;
    }


    //delete monster
    for (int i = (int) enemies.size() - 1; i >= 0; i--) {
        enemies[i]->StateUpdate();

        if (enemies[i]->state == isDead) {
            std::swap(enemies[i], enemies.back());
            enemies.pop_back();
        }
    }

    for(auto enemy : enemies) enemy->FrameUpdate();

        //std::cerr << playerHealth << "\n";
    //std::cerr<< debug1 <<" "<<debug2 <<"\n";

    if (playerHealth <= 0) {
        gameState = gameMenu;
        playerHealth = 50;
        CleanGame();
    }

    //std::cerr << debug1 << " " <<debug2 <<"\n";
}

void Manager::RenderGame() {
    SDL_RenderClear(renderer);

    // background
    gameBackgroundSky->Render();
    gameBackgroundLand->Render();


    for (auto enemy:enemies)
        enemy->Render();

    for (auto enemy:enemies)
        enemy->word->RenderWord();

    SDL_RenderPresent(renderer);
}

void Manager::Clean() {
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void Manager::RenderEnded() {
    SDL_RenderClear(renderer);
    /*gameBackground->Render(0);
    for (auto enemy:enemies)
        enemy->Render();

    for (auto enemy:enemies)
        enemy->word->RenderWord();

    gameOver->Render();*/

    SDL_RenderPresent(renderer);
}
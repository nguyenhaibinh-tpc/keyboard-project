//
// Created by pc on 09/3/2021.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "Manager.h"
#include "TextureLoader.h"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int rnd(int l, int r) { return l + rng() % (r - l + 1); }

SDL_Renderer *Manager::renderer = nullptr;

Manager::Manager() {
    TTF_Init();
    isRunning = true;
    isAtMenu = true;
}

void Manager::InitDictionary() {
    if (fopen("../words.txt", "r")) {
        std::string tmp;
        std::ifstream cin("../words.txt");
        while (cin >> tmp) {
            dictionary.push_back(tmp);
            if (tmp.size() < 3)
                effortlessWords.push_back(tmp);
            else if (tmp.size() < 6)
                easyWords.push_back(tmp);
            else if (tmp.size() < 10)
                normalWords.push_back(tmp);
            else if (tmp.size() < 14)
                hardWords.push_back(tmp);
            else
                extremeWords.push_back(tmp);
        }
        std::sort(dictionary.begin(), dictionary.end(), [](std::string i, std::string j) {
            return i.size() < j.size();
        });
        cin.close();
    } else {
        std::cout << "Dictionary data not found!";
        exit(0);
    }
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

void Manager::HandleGameEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
    for (auto enemy:enemies)
        enemy->handleEvent(event);
}

void Manager::UpdateGame() {
    menuBackground->Update();

    for(int i=enemies.size()-1;i>=0;--i)
        if(enemies[i]->typed == enemies[i]->word.size()){
            std::swap(enemies[i],enemies.back());
            enemies.pop_back();
        }

    if (enemies.empty() || !rnd(0,10000)) {
        enemies.emplace_back();
        enemies.back() = new Entity(dictionary[rnd(0, dictionary.size() - 1)]);
        enemies[enemies.size()-1]->SetAnimation(TextureLoader::GetAnimation("bird-"));
        enemies[enemies.size()-1]->SetAnimationDelay(120);
    }
    for (auto enemy:enemies) {
        enemy->Update();
    }
}

void Manager::RenderGame() {
    SDL_RenderClear(renderer);
    menuBackground->Render();
    for (auto enemy:enemies)
        enemy->Render();
    SDL_RenderPresent(renderer);
}

void Manager::InitMenu() {
    gameLogo = new Button();
    gameLogo->SetTexture(TextureLoader::LoadTexture("../resources/game-logo.png"));
    gameLogo->SetDestR(300, -50, 400, 400);

    menuBackground = new AnimatedObject();
    menuBackground->SetAnimation(TextureLoader::GetAnimation("menu-background-"));
    menuBackground->SetAnimationDelay(120);
    menuBackground->SetDestR(0, 0, 1000, 600);

    startButton = new Button();
    startButton->SetTexture(TextureLoader::LoadTexture("../resources/menu-button.png"));
    startButton->SetSrcR(0, 0, 625, 125);
    startButton->SetDestR(422, 100 + 250, 156, 31);

    optionsButton = new Button();
    optionsButton->SetTexture(TextureLoader::LoadTexture("../resources/menu-button.png"));
    optionsButton->SetSrcR(0, 125, 625, 162);
    optionsButton->SetDestR(422, 140 + 250, 156, 40);

    exitButton = new Button();
    exitButton->SetTexture(TextureLoader::LoadTexture("../resources/menu-button.png"));
    exitButton->SetSrcR(0, 287, 625, 125);
    exitButton->SetDestR(422, 180 + 250, 156, 31);

    handPointer = new Button();
    handPointer->SetTexture(TextureLoader::LoadTexture("../resources/hand-pointer.png"));
    //handPointer->SetTexture(TextureLoader::LoadText("lozchinese",25,0));
    handPointer->SetDestR(590, 355, 30, 25);
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
                            isAtMenu = false;
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
    menuBackground->Update();
}

void Manager::RenderMenu() {
    SDL_RenderClear(renderer);
    menuBackground->Render();
    gameLogo->Render();
    startButton->Render(1);
    optionsButton->Render(1);
    exitButton->Render(1);
    handPointer->Render();
    SDL_RenderPresent(renderer);
}

void Manager::Clean() {
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
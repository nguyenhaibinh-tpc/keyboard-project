//
// Created by pc on 09/3/2021.
//

#include <iostream>
#include "Manager.h"
#include "TextureLoader.h"

SDL_Renderer *Manager::renderer = nullptr;

Manager::Manager() {
    isRunning = true;
    isAtMenu = true;
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

}

void Manager::UpdateGame() {

}

void Manager::RenderGame() {


}

void Manager::InitMenu() {
    gameLogo = new Button();
    gameLogo->SetTexture(TextureLoader::LoadTexture("../resources/game-logo.png"));
    gameLogo->SetDestR(200, -50, 400, 400);

    menuBackground = new AnimatedObject();
    menuBackground->SetAnimation(TextureLoader::GetAnimation("menu-background-"));
    menuBackground->SetAnimationDelay(120);
    menuBackground->SetDestR(0, 0, 800, 600);

    startButton = new Button();
    startButton->SetTexture(TextureLoader::LoadTexture("../resources/menu-button.png"));
    startButton->SetSrcR(0, 0, 625, 125);
    startButton->SetDestR(320, 100 + 250, 156, 31);

    optionsButton = new Button();
    optionsButton->SetTexture(TextureLoader::LoadTexture("../resources/menu-button.png"));
    optionsButton->SetSrcR(0, 125, 625, 162);
    optionsButton->SetDestR(320, 140 + 250, 156, 40);

    exitButton = new Button();
    exitButton->SetTexture(TextureLoader::LoadTexture("../resources/menu-button.png"));
    exitButton->SetSrcR(0, 287, 625, 125);
    exitButton->SetDestR(320, 180 + 250, 156, 31);
}

void Manager::HandleMenuEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
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
    menuBackground->Update();
}

void Manager::RenderMenu() {
    SDL_RenderClear(renderer);
    menuBackground->Render();
    gameLogo->Render();
    startButton->Render(1);
    optionsButton->Render(1);
    exitButton->Render(1);
    SDL_RenderPresent(renderer);
}

void Manager::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
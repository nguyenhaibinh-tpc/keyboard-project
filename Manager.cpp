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
    menuBackground->SetDestR(0,0,800,600);
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
    SDL_RenderPresent(renderer);
}

void Manager::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
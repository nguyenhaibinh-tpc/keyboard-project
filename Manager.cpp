//
// Created by pc on 09/3/2021.
//

#include <iostream>
#include "Manager.h"

Manager::Manager() {
    isRunning = true;

}

void Manager::Init(const char *title, int x_pos, int y_pos, int width, int height, bool fullscreen) {
    int is_fullscreen = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (!SDL_Init(SDL_INIT_EVERYTHING)) {
        window = SDL_CreateWindow(title, x_pos, y_pos, width, height, is_fullscreen);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    } else {
        std::cout << "Failed to load SDL!\n";
        exit(0);
    }
}

void Manager::HandleEvents() {

}

void Manager::Update() {

}

void Manager::Render() {

}
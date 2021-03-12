#include <iostream>
#include "Manager.h"

Manager *game;

int main(int argc, char *args[]) {
    game = new Manager();

    game->Init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, false);
    game->InitMenu();
    game->InitDictionary();
    while (game->GetIsRunning()) {
        if (game->GetIsAtMenu()) {
            game->HandleMenuEvents();
            game->UpdateMenu();
            game->RenderMenu();
        } else {
            game->HandleGameEvents();
            game->UpdateGame();
            game->RenderGame();
        }
    }
    game->Clean();
    return 0;
}

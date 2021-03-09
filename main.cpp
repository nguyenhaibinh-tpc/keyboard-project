#include <iostream>
#include "Manager.h"

void game() {
    if (1) {

    } else {

    }
}

void render() {

}

int main(int argc, char *args[]) {
    Manager *game = new Manager();

    game->Init("Magic Keyboard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    while (game->getIsRunning()) {
        game->HandleEvents();
        game->Update();
        game->Render();
    }

    return 0;
}

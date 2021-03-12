//
// Created by pc on 09/3/2021.
//

#ifndef MAIN_CPP_TEXTURELOADER_H
#define MAIN_CPP_TEXTURELOADER_H

#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class TextureLoader {
public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static std::vector<SDL_Texture *> GetAnimation(const std::string name);
    static SDL_Texture *LoadText(std::string text, int size, int colorID = 0);
    static SDL_Texture *LoadChar(const char *text, int size, int colorID = 0);


    const SDL_Color grey = {171, 171, 171};
};


#endif //MAIN_CPP_TEXTURELOADER_H

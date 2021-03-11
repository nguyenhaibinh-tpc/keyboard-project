//
// Created by pc on 09/3/2021.
//

#include <vector>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include "TextureLoader.h"
#include "Manager.h"

SDL_Texture *TextureLoader::LoadTexture(const char *fileName) {
    SDL_Surface *tmp = IMG_Load(fileName);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Manager::renderer, tmp);
    SDL_FreeSurface(tmp);
    return tex;
}
std::vector<SDL_Texture *> TextureLoader::GetAnimation(const std::string name) {
    std::vector<SDL_Texture *> ret;
    std::cerr<<"../resources/" + name + std::to_string(0) + ".png"<<"\n";
    if(fopen(("../resources/" + name + std::to_string(0) + ".png").c_str(), "r")){
        std::cerr<<"W";
    }

    for (int i = 0; fopen(("../resources/" + name + std::to_string(i) + ".png").c_str(), "r"); ++i) {
        ret.push_back(TextureLoader::LoadTexture(("../resources/" + name + std::to_string(i) + ".png").c_str()));
    }
    return ret;
}




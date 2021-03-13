//
// Created by pc on 11/3/2021.
//

#include <vector>
#include <iostream>
#include "Object.h"
#include "TextureLoader.h"
#include "Manager.h"

#define FONTSIZEH 22
#define FONTSIZEW 19
#define FONTSPACE FONTSIZEW

std::vector<SDL_KeyCode> typeList = {
        SDLK_a,
        SDLK_b,
        SDLK_c,
        SDLK_d,
        SDLK_e,
        SDLK_f,
        SDLK_g,
        SDLK_h,
        SDLK_i,
        SDLK_j,
        SDLK_k,
        SDLK_l,
        SDLK_m,
        SDLK_n,
        SDLK_o,
        SDLK_p,
        SDLK_q,
        SDLK_r,
        SDLK_s,
        SDLK_t,
        SDLK_u,
        SDLK_v,
        SDLK_w,
        SDLK_x,
        SDLK_y,
        SDLK_z
};

void Object::SetDestR(int x, int y, int w, int h) {

    destR.x = x;
    destR.y = y;
    destR.w = w;
    destR.h = h;
}



void Object::SetSrcR(int x, int y, int w, int h) {
    srcR.x = x;
    srcR.y = y;
    srcR.w = w;
    srcR.h = h;
}

void Object::UpDown(int delay, int UpDis, int DownDis, bool UpFirst) {
    Uint32 currentTime = SDL_GetTicks();
    if(DownDis == -1) DownDis = UpDis;

    if(delay >= 0 && currentTime >= lastMovedTimeX + delay && UpMoved < UpDis && UpFirst){
        destR.y--;
        UpMoved++;

        lastMovedTimeY = currentTime;
    }
    else if(delay >= 0 && currentTime >= lastMovedTimeX + delay && DownMoved < DownDis) {
        destR.y++;
        DownMoved++;

        lastMovedTimeY = currentTime;
    }
    else if(delay >= 0 && currentTime >= lastMovedTimeX + delay && UpMoved < UpDis){
        destR.y--;
        UpMoved++;

        lastMovedTimeY = currentTime;
    }


    if(DownMoved == DownDis && UpMoved == UpDis){
        DownMoved = 0;
        UpMoved = 0;
    }
}
void Object::Left(int delay) {
    Uint32 currentTime = SDL_GetTicks();
    if(delay >= 0 && currentTime >= lastMovedTimeX + delay){
        destR.x--;
        lastMovedTimeX = currentTime;
    }
}

void Animation::SetAnimation(std::vector<SDL_Texture *> animation) {
    Animation::animation = animation;
}

void Animation::RenderAnimation() {
    SDL_RenderCopy(Manager::renderer, objTexture, nullptr, &destR);
}

void Animation::UpdateAnimation() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime >= lastAnimationTime + animationDelay) {
        objTexture = animation[currentAnimation];
        currentAnimation = (currentAnimation + 1) % animation.size();
        lastAnimationTime = currentTime;
    }
}

void Animation::SetAnimationDelay(Uint32 delay) {
    animationDelay = delay;
}

void StillFrame::SetTexture(SDL_Texture *texture) {
    StillFrame::texture = texture;
}
void StillFrame::Render(int state) {
    if(state == 0) SDL_RenderCopy(Manager::renderer, texture, nullptr, &destR);
    else SDL_RenderCopy(Manager::renderer, texture, &srcR, &destR);
}

Word::Word(std::string str) {
    wordTexture.clear();
    Word::word = str;
    color = rand() % 6 + 1;
    for (auto i:str) {
        wordTexture.emplace_back();
        std::string go = "";
        go += i;
        wordTexture.back() = TextureLoader::LoadText(go, 24, 0);
    }

    typed = 0;
}

void Word::handleEvent(SDL_Event event) {
    switch (event.type) {
        case SDL_KEYDOWN:
            if (typed < word.size() && event.key.keysym.sym == typeList[word[typed] - 'a']) {
                std::string go = "";
                go += Word::word[typed];
                wordTexture[typed] = TextureLoader::LoadText(go, 24, color);
                typed++;
            }
            break;
        default:
            break;
    }
}

void Word::RenderWord() {
    auto tmpR = destR;
    for (int i = 0; i < wordTexture.size(); ++i) {
        tmpR.x += FONTSPACE;
        SDL_RenderCopy(Manager::renderer, wordTexture[i], nullptr, &tmpR);
    }
}
bool Word::Complete() const {
    return typed == word.size();
}

#define BIRDSIZEW 120
#define BIRDSIZEH 100

#define BATSIZEW 100
#define BATSIZEH 80

#define KNIGHTSIZEW 298
#define KNIGHTSIZEH 152
Enemy::Enemy(int enemyType, std::string str) {
    Enemy::enemyType = enemyType;

    if(enemyType == enemyBird){
        randVar1 = rnd(10,20);
        randVar2 = rnd(10,20);
        randVar3 = rnd(0,1);

        word = new Word(str);
        damage = 7;

        frameCycle.SetDestR(WINDOWSIZEW, rand() % 400 + 100, BIRDSIZEW, BIRDSIZEH);
        word->SetDestR(frameCycle.destR.x - (FONTSPACE*(int)word->word.size()/2 ) + 25/*padding*/,frameCycle.destR.y, FONTSIZEW, FONTSIZEH);

        frameCycle.SetAnimation(TextureLoader::GetAnimation("bird-"));
        frameCycle.SetAnimationDelay(120);
    }
    else if(enemyType == enemyBat){
        randVar1 = rnd(50,70);
        randVar2 = rnd(50,70);
        randVar3 = rnd(0,1);

        str.resize(1);
        word = new Word(str);

        damage = 3;

        frameCycle.SetDestR(WINDOWSIZEW, rand() % 400 + 100, BATSIZEW, BATSIZEH);
        word->SetDestR(frameCycle.destR.x - (FONTSPACE*(int)word->word.size()/2 ) + 28/*padding*/,frameCycle.destR.y, FONTSIZEW, FONTSIZEH);

        frameCycle.SetAnimation(TextureLoader::GetAnimation("bat-"));
        frameCycle.SetAnimationDelay(90);
    }
    else if(enemyType == enemyKnight){

        word = new Word(str);

        damage = 10;

        frameCycle.SetDestR(WINDOWSIZEW, rand() % 400 + 60, KNIGHTSIZEW, KNIGHTSIZEH);
        frameCycle2.SetDestR(WINDOWSIZEW, rand() % 400 + 60, KNIGHTSIZEW, KNIGHTSIZEH);
        word->SetDestR(frameCycle.destR.x - (FONTSPACE*(int)word->word.size()/2 ) + 143/*padding*/,frameCycle.destR.y+20, FONTSIZEW, FONTSIZEH);

        frameCycle.SetAnimation(TextureLoader::GetAnimation("knight-idle-"));
        frameCycle.SetAnimationDelay(90);
        frameCycle2.SetAnimation(TextureLoader::GetAnimation("knight-move-"));
        frameCycle2.SetAnimationDelay(90);
    }

}

void Enemy::Check() {
    if(word->Complete()) isDead = true;
    else if(frameCycle.destR.x < PLAYERX) isDead = true, Manager::playerHealth-=damage;
}
void Enemy::Update() {
    if(enemyType == enemyBird) {

        frameCycle.UpDown(10, randVar1, randVar2, randVar3);
        frameCycle.Left(8);

        word->UpDown(10, randVar1, randVar2, randVar3);
        word->Left(8);
    }
    if(enemyType == enemyBat) {

        frameCycle.UpDown(5, randVar1, randVar2, randVar3);
        frameCycle.Left(3);

        word->UpDown(5, randVar1, randVar2, randVar3);
        word->Left(3);
    }
    if(enemyType == enemyKnight){
    //    frameCycle.UpDown(5, randVar1, randVar2, randVar3);
        frameCycle.Left(6);

    //    word->UpDown(5, randVar1, randVar2, randVar3);
        word->Left(6);
      //  frameCycle.SetDestR(MIDDLESCREEN, MIDDLESCREEN, KNIGHTSIZEW, KNIGHTSIZEH);
        //frameCycle2.SetDestR(WINDOWSIZEW, rand() % 400 + 60, KNIGHTSIZEW, KNIGHTSIZEH);
        //word->SetDestR(frameCycle.destR.x - (FONTSPACE*(int)word->word.size()/2 ) + 143/*padding*/,frameCycle.destR.y+20, FONTSIZEW, FONTSIZEH);

    }

    frameCycle.UpdateAnimation();
}
void Enemy::Render() {
 //   std::cerr<< word->destR.x <<" "<<word->destR.y<<"\n";

    frameCycle.RenderAnimation();
    word->RenderWord();
}

Enemy::~Enemy() {
    std::cerr << "dead\n";
}


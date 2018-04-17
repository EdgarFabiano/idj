//
// Created by edgar on 17/03/18.
//

#include <iostream>
#include <utility>
#include <Game.h>
#include <Resources.h>

#define INCLUDE_SDL_MIXER

Music::Music() : music(nullptr) {}

Music::Music(string file) : music(nullptr) {
    Open(move(file));
}

Music::~Music() {
    Stop(0);
//    Resources cuida da desalocagem
}

void Music::Play(int times) {
    if (music != nullptr)
        Mix_PlayMusic(music, times);
    else {
        cout << "No music loaded: " << SDL_GetError() << endl;
        exit(1);
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Resources::GetMusic(move(file));
}

bool Music::IsOpen() {
    return music != nullptr;
}

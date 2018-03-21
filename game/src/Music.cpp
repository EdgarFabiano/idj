//
// Created by edgar on 17/03/18.
//

#include <iostream>

#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"

#include "../include/Music.h"

Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    Open(file);
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
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
    music = Mix_LoadMUS(file.c_str());
    if(music == nullptr){
        cout << "Unable to load music: " << SDL_GetError() << endl;
        exit(1);
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

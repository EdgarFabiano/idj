//
// Created by edgar on 24/03/18.
//

#include <Game.h>
#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated), chunk(nullptr), channel(0) {}

Sound::Sound(GameObject &associated, string file) : Component(associated), chunk(nullptr), channel(0)  {
    Open(file);
}

Sound::~Sound(){
    if (chunk != nullptr) {
        Stop();
    }
    Mix_FreeChunk(chunk);
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1, chunk, times - 1);
    if(channel == -1){
        cout << "Unable to Mix_PlayChannel: " << SDL_GetError() << endl;
        exit(1);
    }

}

void Sound::Stop(int msToStop) {
    if(chunk != nullptr){
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(string file) {
    chunk = Mix_LoadWAV((ASSETS_PATH + file).c_str());
    if(chunk == nullptr){
        cout << "Unable to Mix_LoadWAV: " << SDL_GetError() << endl;
        exit(1);
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(string type) {
    return type == SOUND_TYPE;
}

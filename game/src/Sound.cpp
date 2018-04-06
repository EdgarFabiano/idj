//
// Created by edgar on 24/03/18.
//

#include <Game.h>
#include <Resources.h>
#include "Sound.h"

Sound::Sound(GameObject &associated) : Component(associated), chunk(nullptr), channel(0) {}

Sound::Sound(GameObject &associated, string file) : Component(associated), chunk(nullptr), channel(0)  {
    Open(file);
}

Sound::~Sound(){
    if (chunk != nullptr) {
        Stop();
    }
// Resources cuida da desalocagem
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
    chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(string type) {
    return type == SOUND_TYPE;
}

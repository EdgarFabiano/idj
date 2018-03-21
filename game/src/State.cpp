//
// Created by edgar on 16/03/18.
//

#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/State.h"

State::State() : bg("../img/ocean.jpg") {
    LoadAssets();
    quitRequested = false;
    music.Play();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    music.Open("../audio/stageState.ogg");
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();

}

void State::Render() {
    bg.Render(0, 0);
}

State::~State() {
	
}
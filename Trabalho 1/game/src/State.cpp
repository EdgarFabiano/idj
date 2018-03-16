//
// Created by edgar on 16/03/18.
//

#include <SDL_quit.h>
#include <SDL_events.h>
#include "../include/State.h"

State::State() {
    quitRequested = false;
    bg = new Sprite();

}

bool State::QuitRequested() {
    return false;
}

void State::LoadAssets() {

}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();

}

void State::Render() {
    bg.Render(0,0);
}

//
// Created by edgar on 11/05/18.
//

#include "TitleState.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include "Game.h"

TitleState::TitleState() {
    auto titleGO(new GameObject);
    titleGO->AddComponent(new Sprite(*titleGO, "img/title.jpg"));
}

TitleState::~TitleState() {

}

void TitleState::LoadAssets() {

}

void TitleState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
    if (inputManager.KeyPress(SPACE_BAR_KEY)) {
        Game::GetInstance().Push(new StageState());
    }
}

void TitleState::Render() {

}

void TitleState::Start() {

}

void TitleState::Pause() {

}

void TitleState::Resume() {

}

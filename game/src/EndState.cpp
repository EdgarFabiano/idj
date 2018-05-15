//
// Created by edgar on 15/05/18.
//

#include <GameData.h>
#include <Sprite.h>
#include <PeriodicEvent.h>
#include <Text.h>
#include <Game.h>
#include <InputManager.h>
#include <TitleState.h>
#include <Camera.h>
#include "EndState.h"

bool  GameData::playerVictory;

EndState::EndState() {
    auto exitTextGO(new GameObject);
    Text *exitText = new Text(*exitTextGO, "font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Press ESC to exit...", {0, 0, 0, 255});
    exitTextGO->AddComponent(exitText);
    Rect &exitFontBox = exitTextGO->box;

    auto restartTextGO(new GameObject);
    Text *restartText = new Text(*restartTextGO, "font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Press space to restart!", {0, 0, 0, 255});
    restartTextGO->AddComponent(restartText);
    Rect &restartFontBox = restartTextGO->box;

    auto bgGO(new GameObject);
    int offset = 0;
    if(GameData::playerVictory){
        bgGO->AddComponent(new Sprite(*bgGO, "img/win.jpg"));
        backgroundMusic.Open("audio/endStateWin.ogg");
        offset = GAME_HEIGHT;
    } else{
        bgGO->AddComponent(new Sprite(*bgGO, "img/lose.jpg"));
        backgroundMusic.Open("audio/endStateLose.ogg");
        offset = (int)(exitFontBox.h + restartFontBox.h);
    }

    AddObject(bgGO);


    exitFontBox.x = GAME_WIDTH/2 - exitFontBox.w/2;
    exitFontBox.y = offset - exitFontBox.h;

    restartFontBox.x = GAME_WIDTH/2 - restartFontBox.w/2;
    restartFontBox.y = offset - restartFontBox.h - exitFontBox.h;


    AddObject(exitTextGO);
    AddObject(restartTextGO);

}

EndState::~EndState() {}

void EndState::LoadAssets() {}

void EndState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
    if (inputManager.KeyPress(SPACE_BAR_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
}

void EndState::Render() {
    RenderArray();
}

void EndState::Start() {
    Camera::pos = Vec2(0, 0);
    StartArray();
    LoadAssets();
    backgroundMusic.Play();
}

void EndState::Pause() {}

void EndState::Resume() {}

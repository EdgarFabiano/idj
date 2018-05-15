//
// Created by edgar on 15/05/18.
//

#include <GameData.h>
#include <Sprite.h>
#include <PeriodicEvent.h>
#include <Text.h>
#include <Game.h>
#include "EndState.h"

EndState::EndState() {
    auto bgGO(new GameObject);
    if(true/*GameData::playerVictory*/){
        bgGO->AddComponent(new Sprite(*bgGO, "img/win.jpg"));
        backgroundMusic.Open("audio/endStateWin.ogg");
    } else{
        bgGO->AddComponent(new Sprite(*bgGO, "img/lose.jpg"));
        backgroundMusic.Open("audio/endStateLose.ogg");
    }
    AddObject(bgGO);

    auto fontGO(new GameObject);
    Text *text = new Text(*fontGO, "font/Call me maybe.ttf", 40, Text::TextStyle::BLENDED, "Press ESC to exit...", {0, 0, 0, 255});
    fontGO->AddComponent(text);
    Rect &fontBox = fontGO->box;
    fontBox.x = GAME_WIDTH/2 - fontBox.w/2;
    fontBox.y = GAME_HEIGHT - fontBox.h;

    fontGO->AddComponent(new PeriodicEvent(*fontGO, 0.4, [text] {
        auto alpha = (text->GetColor().a != 0) ? 0 : 255;
        text->setColor({0, 0, 0, (Uint8)alpha});
    }));

    AddObject(fontGO);
}

EndState::~EndState() {}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {

}

void EndState::Render() {

}

void EndState::Start() {
    StartArray();
    LoadAssets();
    backgroundMusic.Play();
}

void EndState::Pause() {

}

void EndState::Resume() {

}

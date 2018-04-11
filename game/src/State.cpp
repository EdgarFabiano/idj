//
// Created by edgar on 16/03/18.
//

#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include "Face.h"
#include "Sound.h"

State::State() {
    auto bgGO(new GameObject());
    bgGO->AddComponent(new CameraFollower(*bgGO));
    bgGO->AddComponent(new Sprite(*bgGO, "img/ocean.jpg"));

    objectArray.emplace_back(bgGO);

    auto mapGO(new GameObject());
    mapGO->box.w = GAME_WIDTH;
    mapGO->box.h = GAME_HEIGHT;

    TileSet *set = new TileSet(64, 64, "img/tileset.png");
    tileMap = new TileMap(*mapGO, "map/tileMap.txt", set);
    mapGO->AddComponent(tileMap);
    objectArray.emplace_back(mapGO);

    LoadAssets();
    quitRequested = false;
    music.Play();
}

State::~State() {
    objectArray.clear();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    music.Open("audio/stageState.ogg");
}

void State::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();

    Camera::Update(dt);

    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();
    int mouseX = inputManager.GetMouseX(), mouseY = inputManager.GetMouseY();

    if(inputManager.KeyPress(SPACE_BAR_KEY)){
        Vec2 objPos = Vec2(200, 0).Rotate((float) (-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY);
        AddObject(objPos.x, objPos.y);
    }

    for (auto &it : objectArray) {
        it->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render() {
    for (auto &it : objectArray) {
        it->Render();
    }
}

void State::AddObject(int mouseX, int mouseY) {
    auto go(new GameObject());
    Sprite *sprite = new Sprite(*go, "img/penguinface.png");

    go->box.x = mouseX + Camera::pos.x - go->box.w / 2;
    go->box.y = mouseY + Camera::pos.y - go->box.h / 2;

    go->AddComponent(sprite);

    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray.emplace_back(go);
}
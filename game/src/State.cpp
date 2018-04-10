//
// Created by edgar on 16/03/18.
//

#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include "Face.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"

State::State() {
    GameObject *bgGO = new GameObject();
    bgGO->AddComponent(new Sprite(*bgGO, "img/ocean.jpg"));
    objectArray.emplace_back(bgGO);

    GameObject *mapGO = new GameObject();
    mapGO->box.x = 0;
    mapGO->box.y = 0;
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
        AddObject((int)objPos.x, (int)objPos.y);
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
        for (int z = 0; z < tileMap->GetDepth(); z++) {
            tileMap->RenderLayer(z, (int)Camera::pos.x, (int)Camera::pos.y);
        }
    }

}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *go = new GameObject();
    Sprite *sprite = new Sprite(*go, "img/penguinface.png");

    go->box.x = Camera::pos.x + mouseX - go->box.w/2;
    go->box.y = Camera::pos.y + mouseY - go->box.h/2;

    go->AddComponent(sprite);

    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray.emplace_back(go);

}

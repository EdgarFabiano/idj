//
// Created by edgar on 16/03/18.
//

#include <Game.h>
#include <InputManager.h>
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
    mapGO->box.w = SCREEN_SIZE_W;
    mapGO->box.h = SCREEN_SIZE_H;

    TileSet *set = new TileSet(64, 64, "img/tileset.png");
    mapGO->AddComponent(new TileMap(*mapGO, "map/tileMap.txt", set));
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

    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();
    int mouseX = inputManager.GetMouseX(), mouseY = inputManager.GetMouseY();

    if(inputManager.KeyPress(SPACE_BAR_KEY)){
        Vec2 objPos = Vec2(200, 0).GetRotated((float)(-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY );
        AddObject((int)objPos.x, (int)objPos.y);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render() {
    for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
        (*it)->Render();
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *go = new GameObject();
    Sprite *sprite = new Sprite(*go, "img/penguinface.png");

    go->box.x = mouseX - go->box.w/2;
    go->box.y = mouseY - go->box.h/2;

    go->AddComponent(sprite);

    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray.emplace_back(go);

}

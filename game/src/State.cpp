//
// Created by edgar on 16/03/18.
//

#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>

State::State() {
    started = false;
    auto bgGO(new GameObject);
    bgGO->AddComponent(new CameraFollower(*bgGO));
    bgGO->AddComponent(new Sprite(*bgGO, "img/ocean.jpg"));

    objectArray.emplace_back(bgGO);

    auto mapGO(new GameObject);
    mapGO->box.w = GAME_WIDTH;
    mapGO->box.h = GAME_HEIGHT;

    TileSet *tileSet = new TileSet(64, 64, "img/tileset.png");
    TileMap *tileMap = new TileMap(*mapGO, "map/tileMap.txt", tileSet);
    mapGO->AddComponent(tileMap);
    objectArray.emplace_back(mapGO);

    auto alienGO(new GameObject);
    Rect &alienBox = alienGO->box;
    alienBox += {512 + alienBox.w/2, 300 + alienBox.h/2};
    alienGO->AddComponent(new Alien(*alienGO, 5));
    objectArray.emplace_back(alienGO);

    quitRequested = false;
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
        AddObject((int)(objPos.x), (int)(objPos.y));
    }

    for (auto &it : objectArray) {
        it->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
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

    go->box.x = mouseX + Camera::pos.x - go->box.w / 2;
    go->box.y = mouseY + Camera::pos.y - go->box.h / 2;

    objectArray.emplace_back(go);
}

void State::Start() {
    LoadAssets();
    music.Play();
    for (auto &i : objectArray) {
        i->Start();
    }
    started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject *go) {
    shared_ptr<GameObject> gameObject(go);
    objectArray.push_back(gameObject);
    if(started){
        gameObject->Start();
    }
    return weak_ptr<GameObject>(gameObject);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for (auto &i : objectArray) {
        if(i.get() == go){
            return weak_ptr<GameObject>(i);
        }
    }
    return weak_ptr<GameObject>();
}

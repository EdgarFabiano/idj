//
// Created by edgar on 16/03/18.
//

#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include <PenguinBody.h>
#include <StageState.h>
#include <EndState.h>
#include <GameData.h>

StageState::StageState() {
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

    auto penguinBodyGO(new GameObject);
    penguinBodyGO->box += {704, 640};
    penguinBodyGO->AddComponent(new PenguinBody(*penguinBodyGO));
    Camera::Follow(penguinBodyGO);
    objectArray.emplace_back(penguinBodyGO);

    auto alienGO(new GameObject);
    Rect &alienBox = alienGO->box;
    alienBox += {512 + alienBox.w/2, 300 + alienBox.h/2};
    alienGO->AddComponent(new Alien(*alienGO, 5));
    objectArray.emplace_back(alienGO);

    quitRequested = false;
}

StageState::~StageState() {
    objectArray.clear();
}

void StageState::LoadAssets() {
    backgroundMusic.Open("audio/stageState.ogg");
}

void StageState::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();

    Camera::Update(dt);

    quitRequested = inputManager.QuitRequested();

    popRequested = inputManager.KeyPress(ESCAPE_KEY);

    if(inputManager.KeyPress(SDLK_F6)) {
        setDebug(!isDebug());
    }

    UpdateArray(dt);

    if (Alien::alienCount == 0 || PenguinBody::player == nullptr) {
        GameData::playerVictory = PenguinBody::player != nullptr;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }

    IsDeadArray();

    TestCollision();

}

void StageState::Render() {
    for (auto &it : objectArray) {
        it->Render();
    }
}

void StageState::Start() {
    StartArray();
    LoadAssets();
    backgroundMusic.Play();
}

void StageState::Pause() {}

void StageState::Resume() {}


//
// Created by edgar on 16/03/18.
//

#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include <PenguinBody.h>
#include <Collider.h>
#include <Collision.h>
#include <Bullet.h>
#include <Minion.h>

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

    auto penguinBodyGO(new GameObject);
    penguinBodyGO->box += {704, 640};
    penguinBodyGO->AddComponent(new PenguinBody(*penguinBodyGO));
    Camera::Follow(penguinBodyGO);
    objectArray.emplace_back(penguinBodyGO);

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

    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }

    for (int i = 0; i < objectArray.size(); i++) {
        for(int j = i+1; j < objectArray.size(); j++){
            auto &objA = objectArray[i];
            auto &objB = objectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent(COLLIDER_TYPE);
            Collider *colliderB = (Collider*) objB->GetComponent(COLLIDER_TYPE);
            if(colliderA && colliderB){
                auto boxA = colliderA->box;
                auto boxB = colliderB->box;

                auto angleOfA = (float)(objA->angleDeg);
                auto angleOfB = (float)(objB->angleDeg);

                if (Collision::IsCollidingDeg(objA->box, objB->box, angleOfA, angleOfB)) {
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
            }
        }
    }

}

void State::Render() {
    for (auto &it : objectArray) {
        it->Render();
    }
}

void State::Start() {
    LoadAssets();
    music.Play();
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Start();
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

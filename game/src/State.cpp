//
// Created by edgar on 10/05/18.
//

#include "State.h"

State::State() : popRequested(false), quitRequested(false), started(false) {}

State::~State() {
    for(auto it = objectArray.rbegin(); it != objectArray.rend(); ++it) {
        (*it).reset();
    }
    objectArray.clear();
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

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
//    LoadAssets();
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Start();
    }
    started = true;
}

void State::UpdateArray(float dt) {
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Update(dt);
    }
}

void State::RenderArray() {
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[i].get()->Render();
    }
}

bool State::isDebug() const {
    return debug;
}

void State::setDebug(bool debug) {
    this->debug = debug;
}

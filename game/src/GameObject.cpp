//
// Created by edgar on 23/03/18.
//

#include "GameObject.h"

GameObject::GameObject() : isDead(false), started(false), angleDeg(0) {}

GameObject::~GameObject() {
    for(auto it = components.rbegin(); it != components.rend(); ++it) {
        (*it).reset();
    }
    components.clear();
}

void GameObject::Start() {
    for (auto &component : components) {
        component->Start();
    }
    started = true;
}

void GameObject::Update(float dt) {
    for (auto &component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto &component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    components.emplace_back(cpt);
    if(started){
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component *cpt) {
    for(int i = 0; i < components.size(); ++i){
        if(components[i].get() == cpt){
            components.erase(components.begin() + i);
            break;
        }
    }
}

Component *GameObject::GetComponent(string type) {
    for(int i = 0; i < components.size(); i++){
        if(components[i]->Is(type)){
            return components[i].get();
        }
    }
    return nullptr;
}

void GameObject::NotifyCollision(GameObject &other) {
    for(int i = 0; i < components.size(); i++){
        components[i]->NotifyCollision(other);
    }
}

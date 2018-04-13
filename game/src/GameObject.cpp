//
// Created by edgar on 23/03/18.
//

#include <algorithm>
#include "GameObject.h"

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    for (auto &component : components) {
        delete component.get();
    }
    components.clear();
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
    for (auto &component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}

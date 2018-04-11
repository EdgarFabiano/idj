//
// Created by edgar on 23/03/18.
//

#include <algorithm>
#include "GameObject.h"

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
    for(auto it = components.rbegin(); it != components.rend(); ++it) {
        (*it).reset();
    }
}

void GameObject::Update(float dt) {
    for (auto it = components.begin(); it != components.end(); ++it){
        (*it)->Update(dt);
    }
}

void GameObject::Render() {
    for (auto it = components.begin(); it != components.end(); ++it){
        (*it)->Render();
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
    components.erase(remove(components.begin(), components.end(), *new unique_ptr<Component>(cpt)));
}

Component *GameObject::GetComponent(string type) {
    for(auto it = components.begin(); it != components.end(); ++it) {
        if ((*it)->Is(type)) {
            return (*it).get();
        }
    }
    return nullptr;
}

//
// Created by edgar on 23/03/18.
//

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : isDead(false) {}

GameObject::~GameObject() {
//    for(auto i = components.size() - 1; i >= 0; --i){
//        delete components[i];
//    }

    for (auto it = components.begin(); it != components.end(); ++it){
        delete (*it);
    }

    components.clear();
    components.shrink_to_fit;
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
//    if(!components.empty()){
//        for(auto i = 0; i < components.size(); ++i){
//            if(components[i] == cpt){
//                components.erase(components.begin() + i);
//                break;
//            }
//        }
//    }

    for(auto it = components.begin(); it != components.end(); ++it){
        if((*it) == cpt){
            components.erase(it);
            break;
        }
    }
}

Component *GameObject::GetComponent(string type) {
    for(auto it = components.begin(); it != components.end(); ++it) {
        if ((*it)->Is(type)) {
            return (*it);
        }
    }
    return nullptr;
}

//
// Created by edgar on 23/03/18.
//

#ifndef SRC_GAMEOBJECT_H
#define SRC_GAMEOBJECT_H

#include <iostream>
#include <vector>
#include <memory>
#include "Rect.h"
#include "Component.h"

using namespace std;

class Component;

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    Rect box;
    void Start();

private:
    vector<unique_ptr<Component>> components;
    bool isDead;
    bool started;

};


#endif //SRC_GAMEOBJECT_H

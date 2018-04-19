//
// Created by edgar on 18/04/18.
//

#include <Sprite.h>
#include "Minion.h"

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(associated), arc(arcOffsetDeg) {
    associated.AddComponent(new Sprite(associated, "img/minion.png"));
}

void Minion::Update(float dt) {
    Vec2 offset = {0, 0};
    if(!arc){
        offset = {200, 0};
    }
}

void Minion::Render() {

}

bool Minion::Is(string type) {
    return false;
}

void Minion::Shoot(Vec2 target) {

}


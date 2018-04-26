//
// Created by edgar on 25/04/18.
//

#include <Sprite.h>
#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated), pbody(move(penguinBody)), angle(0) {
    this->associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
}

void PenguinCannon::Update(float dt) {

}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
    return false;
}

void PenguinCannon::Shoot() {

}

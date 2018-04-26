//
// Created by edgar on 25/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Game.h>
#include <Bullet.h>
#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated), pbody(move(penguinBody)), angle(0) {
    this->associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
}

void PenguinCannon::Update(float dt) {
    GameObject &body = *pbody.lock();
    if(body.IsDead()){
        associated.RequestDelete();
    }

    InputManager &inputManager = InputManager::GetInstance();

    associated.box = body.box;
    angle = (inputManager.GetMouse() - associated.box.CenterCoord()).InclX();
    associated.angleDeg = angle * 180/M_PI;
    
    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        Shoot();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type) {
    return type == PENGUIN_CANNON_TYPE;
}

void PenguinCannon::Shoot() {
    auto bulletGo = new GameObject;
    auto offset = Vec2(BULLET_OFFSET, 0).Rotate(angle);

    bulletGo->box.x = associated.box.CenterCoord().x - bulletGo->box.w/2;
    bulletGo->box.y = associated.box.CenterCoord().y - bulletGo->box.h/2;
    bulletGo->box += offset;

    bulletGo->angleDeg = angle * 180 / M_PI;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 500, 30, 500, "img/penguinbullet.png", 4, 0.1));

    Game::GetInstance().GetState().AddObject(bulletGo);
}

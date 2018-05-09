//
// Created by edgar on 25/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Game.h>
#include <Bullet.h>
#include <Collider.h>
#include "PenguinCannon.h"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated), pbody(move(penguinBody)), angle(0) {
    associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
    associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Update(float dt) {
    GameObject &body = *pbody.lock();
    if(body.IsDead()){
        associated.RequestDelete();
    }

    InputManager &inputManager = InputManager::GetInstance();

    associated.box = body.box;
    angle = (inputManager.GetMouse() - associated.box.GetCenter()).InclX();
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

    bulletGo->box.x = associated.box.GetCenter().x - bulletGo->box.w/2 + offset.x;
    bulletGo->box.y = associated.box.GetCenter().y - bulletGo->box.h/2 + offset.y;

    bulletGo->angleDeg = angle * 180 / M_PI;
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 10, 30, 1000, "img/penguinbullet.png", 4, 0.1, false));

    Game::GetInstance().GetState().AddObject(bulletGo);
}

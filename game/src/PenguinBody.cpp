//
// Created by edgar on 25/04/18.
//

#include <Sprite.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <InputManager.h>
#include <Collider.h>
#include <Bullet.h>
#include "PenguinBody.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated), speed(0, 0), linearSpeed(0), angle(0), hp(100) {
    associated.AddComponent(new Sprite(associated, "img/penguin.png"));
    associated.AddComponent(new Collider(associated));
    player = this;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    auto *pcannonGO = new GameObject;
    pcannonGO->AddComponent(new PenguinCannon(*pcannonGO,
                                              Game::GetInstance().GetState().GetObjectPtr(&associated)));

    pcannon = Game::GetInstance().GetState().AddObject(pcannonGO);
}

void PenguinBody::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();

    /*Aceleracao*/
    if(inputManager.IsKeyDown(W_KEY) || inputManager.IsKeyDown(S_KEY)) {
        if (inputManager.IsKeyDown(W_KEY) && linearSpeed < PENGUIN_MAX_SPEED) {
            linearSpeed += PENGUIN_ACCELERATION * dt * dt / 2;
        }

        if (inputManager.IsKeyDown(S_KEY) && linearSpeed > -PENGUIN_MAX_SPEED) {
            linearSpeed -= PENGUIN_ACCELERATION * dt * dt / 2;
        }
    }
    /*Atrito*/
    else {
        /*Limite para estabilizar a velocidade em 0*/
        if(abs(linearSpeed) < PENGUIN_SPEED_THRESHOLD) {
            linearSpeed = 0;
        }

        if (linearSpeed > 0) {
            linearSpeed -= PENGUIN_FRICTION * dt * dt / 2;
        } else if (linearSpeed < 0) {
            linearSpeed += PENGUIN_FRICTION * dt * dt / 2;
        }
    }

    if (inputManager.IsKeyDown(A_KEY)){
        angle -= PENGUIN_ANGULAR_SPEED * dt;
    }

    if (inputManager.IsKeyDown(D_KEY)){
        angle += PENGUIN_ANGULAR_SPEED * dt;
    }

    associated.angleDeg = angle;
    speed = Vec2(linearSpeed , 0).RotateDeg(angle);
    associated.box += speed;

    if(hp <= 0){
        associated.RequestDelete();
        (*pcannon.lock()).RequestDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type) {
    return type == PENGUIN_BODY_TYPE;
}

void PenguinBody::NotifyCollision(GameObject &other) {
//    auto bullet = (Bullet*) other.GetComponent(BULLET_TYPE);
//
//    if (bullet) {
//        hp -= bullet->GetDamage();
//    }
}

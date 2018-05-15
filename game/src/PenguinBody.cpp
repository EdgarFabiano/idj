//
// Created by edgar on 25/04/18.
//

#include <Sprite.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <InputManager.h>
#include <Collider.h>
#include <Bullet.h>
#include <Camera.h>
#include <Sound.h>
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
                                              Game::GetInstance().GetCurrentState().GetObjectPtr(&associated)));

    pcannon = Game::GetInstance().GetCurrentState().AddObject(pcannonGO);
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

    Rect borders = {0, 0, 1408, 1280};
    if(associated.box.x > borders.w - associated.box.w){
        associated.box.x = borders.w - associated.box.w;
    } else if(associated.box.x < 0){
        associated.box.x = 0;
    }

    if(associated.box.y > borders.h - associated.box.h){
        associated.box.y = borders.h - associated.box.h;
    } else if(associated.box.y < 0){
        associated.box.y = 0;
    }

    associated.angleDeg = angle;
    speed = Vec2(linearSpeed , 0).RotateDeg(angle);
    associated.box += speed;

    if(hp <= 0){
        associated.RequestDelete();
        (*pcannon.lock()).RequestDelete();
        Camera::Unfollow();

        auto explosionGO(new GameObject());
        explosionGO->AddComponent(new Sprite(*explosionGO, "img/penguindeath.png", 5, 0.1, 0.5));
        explosionGO->box.x = associated.box.GetCenter().x - explosionGO->box.w/2;
        explosionGO->box.y = associated.box.GetCenter().y - explosionGO->box.h/2;;

        auto explosionSound(new Sound(*explosionGO, "audio/boom.wav"));
        explosionGO->AddComponent(explosionSound);
        explosionSound->Play();

        Game::GetInstance().GetCurrentState().AddObject(explosionGO);

    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type) {
    return type == PENGUIN_BODY_TYPE;
}

void PenguinBody::NotifyCollision(GameObject &other) {
    auto enemyBullet = (Bullet*) other.GetComponent(BULLET_TYPE);

    if (enemyBullet && enemyBullet->targetsPlayer) {
        hp -= enemyBullet->GetDamage();
    }
}

Vec2 PenguinBody::GetCenterPosition() {
    return associated.box.GetCenter();
}

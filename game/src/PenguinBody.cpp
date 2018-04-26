//
// Created by edgar on 25/04/18.
//

#include <Sprite.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include "PenguinBody.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated), speed(0, 0), linearSpeed(0), angle(0), hp(100) {
    this->associated.AddComponent(new Sprite(associated, "img/penguin.png"));
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
    auto posX = (int)(inputManager.GetMouseX() + Camera::pos.x), posY = (int)(inputManager.GetMouseY() + Camera::pos.y);


    /*Aceleracao*/
    if(inputManager.IsKeyDown(W_KEY) || inputManager.IsKeyDown(S_KEY)) {
        if (inputManager.IsKeyDown(W_KEY) && speed.x < PENGUIN_MAX_SPEED) {
            speed += Vec2((PENGUIN_ACCELERATION * dt * dt) / 2, 0);
        }

        if (inputManager.IsKeyDown(S_KEY) && speed.x > -PENGUIN_MAX_SPEED) {
            speed -= Vec2((PENGUIN_ACCELERATION * dt * dt) / 2, 0);
        }
    }
    /*Atrito*/
    else {
        /*Limite para estabilizar a velocidade em 0*/
        if(abs(speed.x) < PENGUIN_SPEED_THRESHOLD) {
            speed.x = 0;
        }

        if (speed.x > 0) {
            speed -= Vec2((dt * dt * PENGUIN_FRICTION) / 2, 0);
        } else if (speed.x < 0) {
            speed += Vec2((dt * dt * PENGUIN_FRICTION) / 2, 0);
        }
    }

    

    associated.box += speed;

    if(hp <= 0){
        associated.RequestDelete();
        (*pcannon.lock()).RequestDelete();
    }
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
    return false;
}

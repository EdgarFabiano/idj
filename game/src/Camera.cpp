//
// Created by edgar on 09/04/18.
//

#include <Game.h>
#include <InputManager.h>
#include "Camera.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject *Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus != nullptr){
        pos = {focus->box.x - GAME_WIDTH/2, focus->box.y - GAME_HEIGHT/2};
    } else {
        InputManager inputManager = InputManager::GetInstance();

        speed = {0, 0};
        Vec2 atual = {CAMERA_SPEED * dt, 0};

        if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed = atual;
        } else if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
            speed = atual.Rotate((float)M_PI / 2);
        } else if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
            speed = atual.Rotate((float)M_PI);
        } else if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
            speed = atual.Rotate((float)-M_PI / 2);
        }
        pos += speed;
    }
}

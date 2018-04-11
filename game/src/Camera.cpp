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

        bool right = inputManager.IsKeyDown(RIGHT_ARROW_KEY);
        bool down = inputManager.IsKeyDown(DOWN_ARROW_KEY);
        bool left = inputManager.IsKeyDown(LEFT_ARROW_KEY);
        bool up = inputManager.IsKeyDown(UP_ARROW_KEY);
        
        if (right) {
            speed = atual;
        } else if (down) {
            speed = atual.Rotate((float)M_PI / 2);
        } else if (left) {
            speed = atual.Rotate((float)M_PI);
        } else if (up) {
            speed = atual.Rotate((float)-M_PI / 2);
        }

        if(right && down){
            speed = atual.Rotate((float) 0.79);
        } else if(left && down){
            speed = atual.Rotate((float) 2.36);
        } else if(left && up){
            speed = atual.Rotate((float) 3.93);
        } else if(right && up){
            speed = atual.Rotate((float) 5.5);
        }
        pos += speed;
    }
}

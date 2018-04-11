//
// Created by edgar on 24/03/18.
//

#include <Sound.h>
#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include "Face.h"

Face::Face(GameObject &associated) : Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        ((Sound *) associated.GetComponent(SOUND_TYPE))->Play();
        associated.RequestDelete();
    }
}

void Face::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();
    int mouseX = inputManager.GetMouseX(), mouseY = inputManager.GetMouseY();

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains({(float)mouseX + Camera::pos.x, (float)mouseY + Camera::pos.y})){
        Damage(rand() % 10 + 10);
        return;
    }
}

void Face::Render() {}

bool Face::Is(string type) {
    return type == FACE_TYPE;
}

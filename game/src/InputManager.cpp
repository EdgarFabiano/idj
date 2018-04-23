//
// Created by edgar on 06/04/18.
//

#include <cstring>
#include <Camera.h>
#include "InputManager.h"


InputManager::InputManager() : updateCounter(0), quitRequested(false), mouseX(0), mouseY(0){
    memset(mouseState, 0, sizeof(mouseState));
    memset(mouseUpdate, 0, sizeof(mouseUpdate));
}

InputManager::~InputManager() = default;

void InputManager::Update() {
    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;

    Uint32 eventType;

    while (SDL_PollEvent(&event)) {
        eventType = event.type;
        switch (eventType){
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if(!event.key.repeat){
                    keyState[event.key.keysym.sym] = eventType == SDL_KEYDOWN;
                    keyUpdate[event.key.keysym.sym] = updateCounter;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouseState[event.button.button] = eventType == SDL_MOUSEBUTTONDOWN;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_QUIT:
                quitRequested = true;

            default:
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

Vec2 InputManager::GetMouse() {
    return {mouseX + Camera::pos.x, mouseY + Camera::pos.y};
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

InputManager &InputManager::GetInstance() {
    static InputManager inputManager;
    return inputManager;
}


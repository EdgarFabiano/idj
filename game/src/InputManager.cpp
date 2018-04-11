//
// Created by edgar on 06/04/18.
//

#include <cstring>
#include <SDL_events.h>
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
        if ((eventType == SDL_KEYDOWN || eventType == SDL_KEYUP) && !event.key.repeat) {
            keyState[event.key.keysym.sym] = (eventType == SDL_KEYDOWN);
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
        else if (eventType == SDL_MOUSEBUTTONDOWN || eventType == SDL_MOUSEBUTTONUP) {
            mouseState[event.button.button] = (eventType == SDL_MOUSEBUTTONDOWN);
            mouseUpdate[event.button.button] = updateCounter;
        }
        else if (eventType == SDL_QUIT) {
            quitRequested = true;
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


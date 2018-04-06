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

InputManager::~InputManager() {

}

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
    return false;
}

bool InputManager::MousePress(int button) {
    return false;
}

bool InputManager::MouseRelease(int button) {
    return false;
}

bool InputManager::IsMouseDown(int button) {
    return false;
}

int InputManager::GetMouseX() {
    return 0;
}

int InputManager::GetMouseY() {
    return 0;
}

bool InputManager::QuitRequested() {
    return false;
}

InputManager &InputManager::GetInstance() {
    static InputManager inputManager;
    return inputManager;
}


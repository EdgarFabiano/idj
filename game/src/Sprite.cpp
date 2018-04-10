//
// Created by edgar on 16/03/18.
//

#define INCLUDE_SDL_IMAGE

#include <Resources.h>
#include <Camera.h>
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
//    Resources cuida da desalocagem
}

void Sprite::Open(string file) {
    texture = Resources::GetImage(file);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    associated.box.h = height;
    associated.box.w = width;
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x; clipRect.y = y;
    clipRect.h = h; clipRect.w = w;
}

void Sprite::Render() {
    Render((int)associated.box.x  - (int)Camera::pos.x, (int)associated.box.y - (int)Camera::pos.y);
}

void Sprite::Render(float x, float y) {
    SDL_Rect dst = { (int)x, (int)y, clipRect.w, clipRect.h };
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(string type) {
    return type == SPRITE_TYPE;
}



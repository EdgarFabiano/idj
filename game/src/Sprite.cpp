//
// Created by edgar on 16/03/18.
//

#define INCLUDE_SDL_IMAGE

#include <Resources.h>
#include <Camera.h>

#include <utility>
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr), scale(1, 1) { }

Sprite::Sprite(GameObject& associated, string file) : Component(associated), texture(nullptr), scale(1, 1) {
    Open(move(file));
}

Sprite::~Sprite() {
//    Resources cuida da desalocagem
}

void Sprite::Open(string file) {
    texture = Resources::GetImage(move(file));

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    associated.box.w = width;
    associated.box.h = height;
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
    SDL_Rect dst = { (int)x, (int)y, (int)(clipRect.w * scale.x), (int)(clipRect.h * scale.x) };
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dst, associated.angleDeg, nullptr , SDL_FLIP_NONE);
}

int Sprite::GetWidth() {
    return (int)(width * scale.x);
}

int Sprite::GetHeight() {
    return (int)(height * scale.y);
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}

void Sprite::Update(float dt) {}

bool Sprite::Is(string type) {
    return type == SPRITE_TYPE;
}

void Sprite::SetScale(float scaleX, float scaleY) {
    auto &box = associated.box;
    if(scaleX != 0){
        scale.x = scaleX;
        box.w = width * scaleX;
        box.x = box.CenterCoord().x - box.w/2;
    }

    if(scaleY != 0){
        scale.y = scaleY;
        box.h = height * scaleY;
        box.y = box.CenterCoord().y - box.h/2;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}

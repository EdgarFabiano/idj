//
// Created by edgar on 26/04/18.
//

#include "Collider.h"

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    Rect aux = Rect();

    aux *= scale;

    const Vec2 &center = associated.box.GetCenter();

    aux.x = center.x - aux.w/2;
    aux.y = center.y - aux.h/2;

    box = aux + offset.RotateDeg(associated.angleDeg);
}

void Collider::Render() {}

bool Collider::Is(string type) {
    return type == COLLIDER_TYPE;
}

void Collider::setScale(const Vec2 &scale) {
    this->scale = scale;
}

void Collider::setOffset(const Vec2 &offset) {
    this->offset = offset;
}

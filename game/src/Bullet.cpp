//
// Created by edgar on 19/04/18.
//

#include <Sprite.h>

#include "Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated) {
    associated.AddComponent(new Sprite(associated, move(sprite)));
    this->speed = Vec2(speed, 0).Rotate(angle);
    this->distanceLeft = maxDistance - associated.box.CenterCoord().Mag();
}

void Bullet::Update(float dt) {
    associated.box += speed * dt;
    distanceLeft -= (speed * dt).Mag();
    if(!distanceLeft){
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
    return type == BULLET_TYPE;
}

int Bullet::getDamage() {
    return damage;
}

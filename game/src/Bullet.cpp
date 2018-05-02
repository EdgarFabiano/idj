//
// Created by edgar on 19/04/18.
//

#include <Sprite.h>
#include <Collider.h>
#include <Alien.h>
#include <PenguinBody.h>

#include "Bullet.h"

Bullet::Bullet(GameObject &associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               string sprite,
               int frameCount,
               float frameTime,
               bool enemyBullet) : Component(associated), damage(damage), enemyBullet(enemyBullet) {
    associated.AddComponent(new Sprite(associated, move(sprite), frameCount, frameTime));
    associated.AddComponent(new Collider(associated));
    this->speed = Vec2(speed, 0).Rotate(angle);
    this->distanceLeft = maxDistance;
}

void Bullet::Update(float dt) {
    associated.box += speed * dt;
    distanceLeft -= (speed * dt).Mag();
    if(distanceLeft < 0){
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
    return type == BULLET_TYPE;
}

int Bullet::GetDamage() {
    return damage;
}

bool Bullet::IsEnemyBullet() const {
    return enemyBullet;
}

void Bullet::NotifyCollision(GameObject &other) {
    if((other.GetComponent(PENGUIN_BODY_TYPE) &&  IsEnemyBullet()) || (other.GetComponent(ALIEN_TYPE) &&  !IsEnemyBullet())){
        associated.RequestDelete();
    }
}

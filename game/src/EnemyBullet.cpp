//
// Created by edgar on 02/05/18.
//

#include <PenguinBody.h>
#include <Collider.h>
#include <Sprite.h>
#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(GameObject &associated, float angle, float speed, int damage, float maxDistance,
                         const string &sprite, int frameCount, float frameTime) : Bullet(associated, angle, speed,
                                                                                         damage, maxDistance, sprite,
                                                                                         frameCount, frameTime) {
    associated.AddComponent(new Sprite(associated, move(sprite), frameCount, frameTime));
    associated.AddComponent(new Collider(associated));
    this->speed = Vec2(speed, 0).Rotate(angle);
    this->distanceLeft = maxDistance;
}

bool EnemyBullet::Is(string type) {
    return type == ENEMY_BULLET_TYPE;
}

void EnemyBullet::NotifyCollision(GameObject &other) {
    if(other.GetComponent(PENGUIN_BODY_TYPE)){
        associated.RequestDelete();
    }
}

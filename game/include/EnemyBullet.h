//
// Created by edgar on 02/05/18.
//

#ifndef ENEMY_BULLET_CLASS
#define ENEMY_BULLET_CLASS

#define ENEMY_BULLET_TYPE "EnemyBullet"


#include "Bullet.h"

class EnemyBullet : public Bullet {
public:
    EnemyBullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, const string &sprite,
                int frameCount, float frameTime);

    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

};


#endif //SRC_ENEMYBULLET_H

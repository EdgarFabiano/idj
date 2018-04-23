//
// Created by edgar on 19/04/18.
//

#ifndef SRC_BULLET_H
#define SRC_BULLET_H

#define BULLET_TYPE "Bullet"

#include "Component.h"

class Bullet : public Component {
public:
    Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    int getDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;

};


#endif //SRC_BULLET_H
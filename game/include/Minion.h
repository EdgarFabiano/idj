//
// Created by edgar on 18/04/18.
//

#ifndef SRC_MINION_H
#define SRC_MINION_H

#define MINION_ANGULAR_SPEED M_PI/8


#include "GameObject.h"

class Minion : public Component {
public:
    Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void  Shoot(Vec2 target);

private:
    GameObject& alienCenter;
    float arc;

};


#endif //SRC_MINION_H

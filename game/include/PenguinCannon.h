//
// Created by edgar on 25/04/18.
//

#ifndef PENGUIN_CANNON_CLASS
#define PENGUIN_CANNON_CLASS

#include "Component.h"

#define PENGUIN_CANNON_TYPE "PenguinCannon"

class PenguinCannon :public Component {
public:
    PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void Shoot();

private:
    weak_ptr<GameObject> pbody;
    float angle;

};


#endif //SRC_PENGUINCANNON_H

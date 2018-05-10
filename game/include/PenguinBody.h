//
// Created by edgar on 25/04/18.
//

#ifndef PENGUIN_BODY_CLASS
#define PENGUIN_BODY_CLASS

#define PENGUIN_BODY_TYPE "PenguinBody"
#define PENGUIN_ACCELERATION 700
#define PENGUIN_FRICTION 500
#define PENGUIN_MAX_SPEED 20
#define PENGUIN_ANGULAR_SPEED 100
#define PENGUIN_SPEED_THRESHOLD 1


#include "Component.h"

class PenguinBody : public Component {
public:
    explicit PenguinBody(GameObject &associated);
    virtual ~PenguinBody();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    static PenguinBody* player;
    Vec2 GetCenterPosition();

private:
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

};


#endif //SRC_PENGUINBODY_H

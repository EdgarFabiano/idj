//
// Created by edgar on 17/04/18.
//

#ifndef ALIEN_CLASS
#define ALIEN_CLASS

#define ALIEN_TYPE "Alien"
#define ALIEN_SPEED 200
#define ALIEN_ROTATION_SPEED -2
#define ALIEN_REST_COOLDOWN 3

#include <queue>
#include "Component.h"
#include "Timer.h"

class Alien : public Component {
public:
    Alien(GameObject &associated, int nMinions, float timeOffset);
    ~Alien();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    static int alienCount;

private:
    Vec2 speed;
    int hp;
    vector<weak_ptr<GameObject>> minionArray;

    int NearestMinion(const Vec2 &target) const;

    enum AlienState{MOVING, RESTING};
    AlienState state = RESTING;
    Timer restTimer;
    Vec2 destination;

    float timeOffset;
};


#endif //SRC_ALIEN_H

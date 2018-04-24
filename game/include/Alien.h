//
// Created by edgar on 17/04/18.
//

#ifndef ALIEN_CLASS
#define ALIEN_CLASS

#define ALIEN_TYPE "Alien"
#define ALIEN_SPEED 500
#define ALIEN_ROTATION_SPEED -2

#include <queue>
#include "Component.h"

class Alien : public Component {
public:
    Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start() override;
    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    class Action{
    public:
        enum ActionType{MOVE, SHOOT};

        Action(ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;

    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;

    int NearestMinion(const Vec2 &target) const;
};


#endif //SRC_ALIEN_H

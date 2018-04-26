//
// Created by edgar on 26/04/18.
//

#ifndef COLLIDER_CLASS
#define COLLIDER_CLASS

#define COLLIDER_TYPE "Collider"

#include <Component.h>

class Collider : public Component {
public:
    Collider(GameObject &associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});

    Rect box;

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    void setScale(const Vec2 &scale);
    void setOffset(const Vec2 &offset);

private:
    Vec2 scale;
    Vec2 offset;

};


#endif //SRC_COLLIDER_H

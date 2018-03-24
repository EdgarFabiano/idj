//
// Created by edgar on 24/03/18.
//

#ifndef SRC_FACE_H
#define SRC_FACE_H

#include "Component.h"

#define FACE_TYPE "Face"

class Face : public Component {
public:
    explicit Face(GameObject &associated);
    void Damage(int damage);

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    int hitpoints;

};


#endif //SRC_FACE_H

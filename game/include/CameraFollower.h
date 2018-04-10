//
// Created by edgar on 10/04/18.
//

#ifndef CAMERAFOLLOWER_CLASS
#define CAMERAFOLLOWER_CLASS


#include <Component.h>

#define CAMERA_FOLLOWER_TYPE "CameraFollower"

class CameraFollower : public Component {
public:
    explicit CameraFollower(GameObject &associated);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

};

#endif //SRC_CAMERAFOLLOWER_H

//
// Created by edgar on 10/04/18.
//

#include <Camera.h>
#include "CameraFollower.h"

CameraFollower::CameraFollower(GameObject &associated) : Component(associated) {

}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

void CameraFollower::Render() {

}

bool CameraFollower::Is(string type) {
    return type == CAMERA_FOLLOWER_TYPE;
}

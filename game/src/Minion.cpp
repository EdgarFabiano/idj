//
// Created by edgar on 18/04/18.
//

#include <Sprite.h>
#include <Bullet.h>
#include <Game.h>
#include "Minion.h"

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(*alienCenter.lock()), arc(arcOffsetDeg) {
    associated.AddComponent(new Sprite(associated, "img/minion.png"));
}

void Minion::Update(float dt) {
    if(associated.IsDead()){
        associated.RequestDelete();
    }
    arc += MINION_ANGULAR_SPEED * dt;
    Vec2 raioOrbita = Vec2(150, 0).Rotate(arc);
    Vec2 distOrigem = alienCenter.box.CenterCoord();

    //adiciona a distancia da origem->alien em cada frame para o centro da orbita de minions
    associated.box += raioOrbita - associated.box.CenterCoord() + distOrigem;

}

void Minion::Render() {}

bool Minion::Is(string type) {
    return type == MINION_TYPE;
}

void Minion::Shoot(Vec2 target) {
    auto bulletGo = new GameObject;
    bulletGo->box.x = associated.box.CenterCoord().x - bulletGo->box.w/2;
    bulletGo->box.y = associated.box.CenterCoord().y - bulletGo->box.h/2;
    float angle = (target - associated.box.CenterCoord()).InclX();
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 800, 30, 1000, "img/minionbullet1.png"));

    Game::GetInstance().GetState().AddObject(bulletGo);
}

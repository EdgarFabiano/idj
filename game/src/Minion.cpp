//
// Created by edgar on 18/04/18.
//

#include <Sprite.h>
#include <Game.h>
#include <Collider.h>
#include <Bullet.h>
#include <Sound.h>
#include "Minion.h"

Minion::Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component(associated), alienCenter(*alienCenter.lock()), arc(arcOffsetDeg) {
    Sprite *sprite = new Sprite(associated, "img/minion.png");
    float random = float_rand(1, 1.5f);
    sprite->SetScale(random, random);
    associated.AddComponent(sprite);
    associated.AddComponent(new Collider(associated));
}

void Minion::Update(float dt) {
    if((alienCenter.IsDead())){

        auto explosionGO(new GameObject());
        explosionGO->AddComponent(new Sprite(*explosionGO, "img/miniondeath.png", 4, 0.1, 0.4));
        explosionGO->box.x = associated.box.GetCenter().x - explosionGO->box.w/2;
        explosionGO->box.y = associated.box.GetCenter().y - explosionGO->box.h/2;
        Game::GetInstance().GetCurrentState().AddObject(explosionGO);

        associated.RequestDelete();
    }
    arc += MINION_ANGULAR_SPEED * dt;
    Vec2 raioOrbita = Vec2(150, 0).Rotate(arc);
    Vec2 distOrigem = alienCenter.box.GetCenter();

    //adiciona a distancia da origem->alien em cada frame para o centro da orbita de minions
    associated.box += raioOrbita - associated.box.GetCenter() + distOrigem;
    associated.angleDeg = raioOrbita.InclX() * 180 / M_PI;

}

void Minion::Render() {}

bool Minion::Is(string type) {
    return type == MINION_TYPE;
}

void Minion::Shoot(Vec2 target) {
    auto bulletGo = new GameObject;
    bulletGo->box.x = associated.box.GetCenter().x - bulletGo->box.w/2;
    bulletGo->box.y = associated.box.GetCenter().y - bulletGo->box.h/2;

    float angle = (target - associated.box.GetCenter()).InclXDeg();
    bulletGo->AddComponent(new Bullet(*bulletGo, angle, 300, 20, 1000, "img/minionbullet2.png", 3, 0.01, true));

    auto explosionSound(new Sound(*bulletGo, "audio/boom.wav"));
    bulletGo->AddComponent(explosionSound);
    explosionSound->Play();

    Game::GetInstance().GetCurrentState().AddObject(bulletGo);
}

float Minion::float_rand( float min, float max ){
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}


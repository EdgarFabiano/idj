//
// Created by edgar on 17/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Minion.h>
#include <Game.h>
#include <Collider.h>
#include <Bullet.h>
#include <Sound.h>
#include <PenguinBody.h>
#include "Alien.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions, float timeOffset) : Component(associated), speed({0, 0}), hp(50), timeOffset(timeOffset) {
    associated.AddComponent(new Sprite(associated, "img/alien.png"));
    associated.AddComponent(new Collider(associated, {0.6, 0.6}, {-9, 0}));
    minionArray.resize((unsigned)(nMinions));
    alienCount++;
}

Alien::~Alien() {
    for (auto &i : minionArray) {
        i.lock()->RequestDelete();
    }
    minionArray.clear();
    alienCount--;
}

void Alien::Start() {
    auto minionSize = minionArray.size();
    for(int i = 0; i < minionSize; i++){
        auto *minionGO = new GameObject;

        //espaca os minions igualmente na orbita em funcao da quantidade
        auto setor = (float)(2 * M_PI * (i /(float)minionSize));

        minionGO->AddComponent(new Minion(*minionGO,
                                          Game::GetInstance().GetCurrentState().GetObjectPtr(&associated),
                                          setor));

        minionArray[i] = (Game::GetInstance().GetCurrentState().AddObject(minionGO));
        restTimer = *new Timer;
    }
}

void Alien::Update(float dt) {
    if(hp <= 0){
        auto explosionGO(new GameObject());
        explosionGO->AddComponent(new Sprite(*explosionGO, "img/aliendeath.png", 4, 0.1, 0.4));
        explosionGO->box.x = associated.box.GetCenter().x - explosionGO->box.w/2;
        explosionGO->box.y = associated.box.GetCenter().y - explosionGO->box.h/2;

        auto explosionSound(new Sound(*explosionGO, "audio/boom.wav"));
        explosionGO->AddComponent(explosionSound);
        explosionSound->Play();

        Game::GetInstance().GetCurrentState().AddObject(explosionGO);

        associated.RequestDelete();
    } else{
        InputManager inputManager = InputManager::GetInstance();

        associated.angleDeg += ALIEN_ROTATION_SPEED;

        PenguinBody *player = PenguinBody::player;
        if(player) {
            if (state == RESTING) {
                restTimer.Update(dt);
                if (restTimer.Get() > ALIEN_REST_COOLDOWN + timeOffset) {
                    destination = player->GetCenterPosition();
                    speed = Vec2(ALIEN_SPEED, 0).Rotate((destination - associated.box.GetCenter()).InclX());
                    state = MOVING;
                }
            } else if (state == MOVING) {
                Vec2 deltaX = {ALIEN_SPEED * dt, 0};
                Vec2 calculado = destination - Vec2(associated.box.x + (associated.box.w/2), associated.box.y + (associated.box.h/2));
                Vec2 real = deltaX.Rotate(calculado.InclX());

                //Distancia minima para o Alien nao chegar ao destino no proximo frame
                if(calculado.Mag() < real.Mag()){
                    //chegou em destination
                    associated.box += calculado;

                    auto target = player->GetCenterPosition();

                    //Pega o minion com a menor distância do alvo
                    const shared_ptr<GameObject> &ptr = minionArray[NearestMinion(target)].lock();
                    auto minion = (Minion*)(ptr->GetComponent(MINION_TYPE));
                    minion->Shoot(target);

                    state = RESTING;
                    restTimer.Restart();
                } else {
                    //deslocando ate destination
                    associated.box += real;
                }

            }
        }
    }

}

void Alien::Render() {}

bool Alien::Is(string type) {
    return type == ALIEN_TYPE;
}

int Alien::NearestMinion(const Vec2 &target) const {
    float minimum = ((*minionArray[0].lock()).box.GetCenter() - target).Mag();
    int location = 0;
    for(int i = 0; i < minionArray.size(); i++){
        float dist = ((*minionArray[i].lock()).box.GetCenter() - target).Mag();
        if (dist < minimum ){
            minimum = dist;
            location = i;
        }
    }
    return location;
}

void Alien::NotifyCollision(GameObject &other) {
    auto bullet = (Bullet*) other.GetComponent(BULLET_TYPE);

    if (bullet && !bullet->targetsPlayer) {
        hp -= bullet->GetDamage();
    }
}

//
// Created by edgar on 17/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Minion.h>
#include <Game.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), speed({0, 0}), hp(50) {
    associated.AddComponent(new Sprite(associated, "img/alien.png"));
    minionArray.resize((unsigned long)(nMinions));
}

Alien::~Alien() {
    for (auto &i : minionArray) {
        i.lock()->RequestDelete();
    }
    minionArray.clear();
}

void Alien::Start() {
    auto minionSize = (float) minionArray.size();
    for(int i = 0; i < minionSize; i++){
        auto *minionGO = new GameObject;

        //espaca os minions igualmente na orbita em funcao da quantidade
        auto setor = (float)(2 * M_PI * (i / minionSize));

        minionGO->AddComponent(new Minion(*minionGO,
                                          Game::GetInstance().GetState().GetObjectPtr(&associated),
                                          setor));

        minionArray[i] = (Game::GetInstance().GetState().AddObject(minionGO));
    }
}

void Alien::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();
    auto posX = (int)(inputManager.GetMouseX() + Camera::pos.x), posY = (int)(inputManager.GetMouseY() + Camera::pos.y);

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)){
        taskQueue.push(*new Action(Action::SHOOT, posX , posY));
    } else if(inputManager.MousePress(RIGHT_MOUSE_BUTTON)){

        //impede de acumular eventos na fila, sobrescrevendo sempre que há um evento
        while(!taskQueue.empty()){
            taskQueue.pop();
        }
        taskQueue.push(*new Action(Action::MOVE, posX, posY));
    }

    if(!taskQueue.empty()){
        auto action = taskQueue.front();

        if(action.type == Action::MOVE){
            Vec2 deltaX = {ALIEN_SPEED * dt, 0};
            Vec2 calculado = action.pos - Vec2(associated.box.x + (associated.box.w/2), associated.box.y + (associated.box.h/2));
            Vec2 real = deltaX.Rotate(calculado.InclX());

            //Distancia minima para o Alien nao chegar ao destino no proximo frame
            if(calculado.Mag() < real.Mag()){
                associated.box += calculado;
                taskQueue.pop();
            } else {
                associated.box += real;
            }

        } else if(action.type == Action::SHOOT){
            auto target = InputManager::GetInstance().GetMouse();
            const shared_ptr<GameObject> &ptr = minionArray[rand() % minionArray.size()].lock();
            auto minion = (Minion*)(ptr->GetComponent(MINION_TYPE));
            minion->Shoot(target);
            taskQueue.pop();
        }
    }

    if(hp <= 0){
        associated.RequestDelete();
    }

}

void Alien::Render() {}

bool Alien::Is(string type) {
    return type == ALIEN_TYPE;
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type){
    pos.x = x;
    pos.y = y;
}
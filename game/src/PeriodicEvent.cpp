//
// Created by edgar on 15/05/18.
//

#include "PeriodicEvent.h"

PeriodicEvent::PeriodicEvent(GameObject &associated, float period, ActionCallback cb) : Component(associated), period(period), timer(Timer()) {
    _callback = move(cb);
}

void PeriodicEvent::Update(float dt) {
    timer.Update(dt);
    if(timer.Get() >= period){
        run();
        timer.Restart();
    }
}

void PeriodicEvent::Render() {}

bool PeriodicEvent::Is(string type) {
    return type == PERIODIC_EVENT_TYPE;
}


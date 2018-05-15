//
// Created by edgar on 15/05/18.
//

#ifndef PERIODEVENT_CLASS
#define PERIODEVENT_CLASS

#include <Timer.h>
#include <functional>
#include "Component.h"

#define PERIODIC_EVENT_TYPE "PeriodicEvent"

class PeriodicEvent : public Component {
public:
    typedef function<void()> ActionCallback;

    PeriodicEvent(GameObject &associated, float period, ActionCallback cb);

    void run()
    {
        _callback();
    }

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    float period;
    Timer timer;

    ActionCallback _callback;
};


#endif //SRC_PERIODEVENT_H

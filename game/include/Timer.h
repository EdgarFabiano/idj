//
// Created by edgar on 09/05/18.
//

#ifndef SRC_TIMER_H
#define SRC_TIMER_H


class Timer {
public:
    Timer();

    void Update(float dt);
    void Restart();
    float Get();

private:
    float time;

};


#endif //SRC_TIMER_H

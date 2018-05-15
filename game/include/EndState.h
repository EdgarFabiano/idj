//
// Created by edgar on 15/05/18.
//

#ifndef ENDSTATE_CLASS
#define ENDSTATE_CLASS


#include "State.h"
#include "Music.h"

class EndState : public State{
public:
    EndState();
    ~EndState();

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music backgroundMusic;
};


#endif //SRC_ENDSTATE_H

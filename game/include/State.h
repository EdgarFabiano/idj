//
// Created by edgar on 16/03/18.
//

#ifndef STATE_CLASS
#define STATE_CLASS

#include "Sprite.h"
#include "Music.h"

class State {
public:
    State ();
    ~State();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();

private:
    Sprite bg;
    Music music;
    bool quitRequested;

};


#endif //SRC_STATE_H

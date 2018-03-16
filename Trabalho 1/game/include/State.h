//
// Created by edgar on 16/03/18.
//

#ifndef SRC_STATE_H
#define SRC_STATE_H


class State {
public:
    State ();
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

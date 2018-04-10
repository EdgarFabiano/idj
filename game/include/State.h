//
// Created by edgar on 16/03/18.
//

#ifndef STATE_CLASS
#define STATE_CLASS

#include "Sprite.h"
#include "Music.h"
#include "TileMap.h"

class State {
public:
    State ();
    ~State();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();

private:
    void AddObject(int mouseX, int mouseY);
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;
    TileMap *tileMap;

};


#endif //SRC_STATE_H

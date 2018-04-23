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
    void Start();
    weak_ptr<GameObject> AddObject(GameObject *go);
    weak_ptr<GameObject> GetObjectPtr(GameObject *go);

private:
    Music music;
    bool quitRequested;
    vector<shared_ptr< GameObject>> objectArray;
    bool started;
};


#endif //SRC_STATE_H

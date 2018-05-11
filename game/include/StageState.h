//
// Created by edgar on 16/03/18.
//

#ifndef STATE_CLASS
#define STATE_CLASS

#include "Sprite.h"
#include "Music.h"
#include "TileMap.h"

class StageState {
public:
    StageState ();
    ~StageState();
    bool QuitRequested ();
    void LoadAssets ();
    void Update (float dt);
    void Render ();
    void Start();
    weak_ptr<GameObject> AddObject(GameObject *go);
    weak_ptr<GameObject> GetObjectPtr(GameObject *go);
    void TestCollision(vector<shared_ptr< GameObject>> &objectArray);
    bool isDebug() const;
    void setDebug(bool debug);

private:
    Music music;
    bool quitRequested;
    vector<shared_ptr< GameObject>> objectArray;
    bool started;
    bool debug = false;

};


#endif //SRC_STATE_H

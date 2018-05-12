//
// Created by edgar on 10/05/18.
//

#ifndef STATE_CLASS
#define STATE_CLASS


#include "GameObject.h"

class State {
public:
    State();
    virtual ~State();

    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual weak_ptr<GameObject> AddObject(GameObject *go);
    virtual weak_ptr<GameObject> GetObjectPtr(GameObject *go);

    bool PopRequested();
    bool QuitRequested();

    bool isDebug() const;
    void setDebug(bool debug);

    void TestCollision();

protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();
    virtual void IsDeadArray();

    bool popRequested;
    bool quitRequested;
    bool started;

    vector<shared_ptr<GameObject>> objectArray;

    bool debug = false;

};


#endif //SRC_STATE_H

//
// Created by edgar on 16/03/18.
//

#ifndef STAGE_STATE_CLASS
#define STAGE_STATE_CLASS

#include "Sprite.h"
#include "Music.h"
#include "TileMap.h"
#include "TileSet.h"
#include "TileMap.h"
#include "State.h"


class StageState : public State {
public:
    StageState ();
    ~StageState();

    void LoadAssets () override;
    void Update (float dt) override;
    void Render () override;

    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    TileSet* tileSet;
    Music backgroundMusic;

};


#endif //SRC_STATE_H

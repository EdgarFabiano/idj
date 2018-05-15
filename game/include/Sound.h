//
// Created by edgar on 24/03/18.
//

#ifndef SOUND_CLASS
#define SOUND_CLASS


#include <Component.h>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define SOUND_TYPE "Sound"

class Sound : public Component{
public:
    explicit Sound(GameObject &associated);
    Sound(GameObject &associated, string file);
    ~Sound() override;

    void Play(int times = 1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

    bool IsSoundPlaying();

private:
    shared_ptr<Mix_Chunk> chunk;
    int channel;


};


#endif //SRC_SOUND_H

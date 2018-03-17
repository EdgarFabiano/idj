//
// Created by edgar on 17/03/18.
//

#ifndef MUSIC_CLASS
#define MUSIC_CLASS

#include <iostream>
#include <SDL_mixer.h>
#include "SDL_include.h"

using namespace std;

class Music {
public:
    Music();
    Music(string file);
    ~Music();
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();

private:
    Mix_Music* music;

};


#endif //SRC_MUSIC_H

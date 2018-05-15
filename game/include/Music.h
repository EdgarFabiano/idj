//
// Created by edgar on 17/03/18.
//

#ifndef MUSIC_CLASS
#define MUSIC_CLASS

#include <iostream>

#define INCLUDE_SDL_MIXER
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
    shared_ptr<Mix_Music> music;

};


#endif //SRC_MUSIC_H

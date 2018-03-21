//
// Created by edgar on 16/03/18.
//

#ifndef SPRITE_CLASS
#define SPRITE_CLASS

#include <iostream>

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

using namespace std;

class Sprite {

public:
    Sprite();
    Sprite(string file);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth() const;
    int GetHeight() const;
    bool IsOpen();

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

};


#endif //SRC_SPRITE_H

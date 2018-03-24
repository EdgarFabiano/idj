//
// Created by edgar on 16/03/18.
//

#ifndef SPRITE_CLASS
#define SPRITE_CLASS

#include <iostream>

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"

#define SPRITE_TYPE "Sprite"

using namespace std;

class Sprite : public Component {

public:
    explicit Sprite(GameObject& associated);
    explicit Sprite(GameObject& associated, string file);
    ~Sprite() override;

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;

private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;

};


#endif //SRC_SPRITE_H

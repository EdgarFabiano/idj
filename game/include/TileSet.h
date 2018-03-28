//
// Created by edgar on 28/03/18.
//

#ifndef TILESET_CLASS
#define TILESET_CLASS

using namespace std;


#include "Sprite.h"

class TileSet {

public:
    TileSet(int tileWidth, int tileHeight, string file);

    void RenderTile(unsigned index, float x, float y);

    int getTileWidth() const;

    int getTileHeight() const;

private:
    Sprite tileSet = nullptr;

    int rows;
    int columns;

    int tileWidth;
    int tileHeight;

};


#endif //SRC_TILESET_H

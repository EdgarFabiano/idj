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

    int GetTileWidth() const;

    int GetTileHeight() const;

private:
    Sprite tileSet;

    int rows;
    int columns;

    int tileWidth;
    int tileHeight;

};


#endif //SRC_TILESET_H

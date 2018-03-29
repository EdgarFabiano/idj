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
<<<<<<< HEAD
    Sprite tileSet;
=======
    Sprite tileSet = nullptr;
>>>>>>> 361173c269c8de760e5b630283503dee473759e7

    int rows;
    int columns;

    int tileWidth;
    int tileHeight;

};


#endif //SRC_TILESET_H

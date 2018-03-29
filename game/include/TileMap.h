//
// Created by edgar on 28/03/18.
//

#ifndef TILEMAP_CLASS
#define TILEMAP_CLASS

using namespace std;

#include "GameObject.h"
#include "TileSet.h"

class TileMap {
public:
    TileMap(GameObject& associated, string file, TileSet* tileSet);

    void Load(string file);

    void SetTileSet(TileSet* tileSet);

    int& At(int x, int y, int z = 0);

    void Render();

    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth();

    int GetHeight();

    int GetDepth();

private:
    vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;

};


#endif //SRC_TILEMAP_H

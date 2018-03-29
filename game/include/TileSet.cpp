//
// Created by edgar on 28/03/18.
//

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileWidth(tileWidth), tileHeight(tileHeight) {
    tileSet.Open(file);
    if(tileSet.IsOpen()){
        rows = tileSet.GetWidth() / tileWidth;
        columns = tileSet.GetHeight() / tileHeight;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < rows*columns - 1){
        tileSet.SetClip(x, y, tileWidth*3, tileHeight*4);
        tileSet.Render();
    }
}

int TileSet::getTileWidth() const {
    return tileWidth;
}

int TileSet::getTileHeight() const {
    return tileHeight;
}

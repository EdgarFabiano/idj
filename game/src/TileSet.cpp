//
// Created by edgar on 28/03/18.
//

#include "TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(*(new GameObject()), file), tileWidth(tileWidth), tileHeight(tileHeight) {
    tileSet.Open(file);
    if(tileSet.IsOpen()){
        rows = tileSet.GetHeight() / tileHeight;
        columns = tileSet.GetWidth() / tileWidth;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < (unsigned)rows*columns - 1){
        int clipX, clipY;
        if(index >= (unsigned) columns){
            int auxLinhas = index/columns;
            int auxRestoLinhas = index % columns;

            clipX = auxRestoLinhas * tileWidth;
            clipY = auxLinhas * tileHeight;
        } else {
            clipX = index * tileWidth;
            clipY = 0;
        }
        tileSet.SetClip(x, y, tileWidth*3, tileHeight*4);
        tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth() const {
    return tileWidth;
}

int TileSet::GetTileHeight() const {
    return tileHeight;
}

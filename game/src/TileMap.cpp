//
// Created by edgar on 28/03/18.
//

#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(string file) {
    FILE* fp = fopen((ASSETS_PATH + file).c_str(), "r");
    if(fp == nullptr){
        std::cout << "Erro ao abrir o arquivo: " << file << std::endl;
        exit(1);
    }

    if(fscanf(fp, "%d,%d,%d", &mapWidth, &mapHeight, &mapDepth) != 3){
        std::cout << "Erro nas dimensoes do arquivo: " << file << std::endl;
        exit(1);
    }

    int scanned;
    fseek(fp, 1, SEEK_CUR);
    while(!feof(fp)){
        fscanf(fp, " %d,", &scanned);
        tileMatrix.push_back(scanned - 1);
    }

    fclose(fp);
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
    int index = x + mapWidth * y + mapWidth * mapHeight * z;
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapWidth; i++){
        for (int j = 0; j < mapHeight; ++j){
            int x = i * tileSet->GetTileWidth() - cameraX;
            int y = j * tileSet->GetTileHeight() - cameraY;

            Rect box = associated.box;

            if (x > -tileSet->GetTileWidth() && x < box.w && y > -tileSet->GetTileHeight() && y < box.h) {
                tileSet->RenderTile((unsigned)At(i, j, layer), x, y);
            }
        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
        RenderLayer(z, (int)associated.box.x, (int)associated.box.y);
    }
}

void TileMap::Update(float dt) {

}

bool TileMap::Is(string type) {
    return type == TILE_MAP_TYPE;
}

int TileMap::GetWidth() {
    return this->mapWidth;
}

int TileMap::GetHeight() {
    return this->mapHeight;
}

int TileMap::GetDepth() {
    return this->mapDepth;
}


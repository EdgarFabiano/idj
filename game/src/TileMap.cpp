//
// Created by edgar on 28/03/18.
//

#include <Camera.h>

#include <utility>
#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated) {
    Load(move(file));
    SetTileSet(tileSet);
}

void TileMap::Load(string file) {
    FILE* fp = fopen((ASSETS_PATH + file).c_str(), "r");
    if(fp == nullptr){
        cout << "Erro ao abrir o arquivo de mapa: " << file << endl;
        exit(1);
    }

    if(fscanf(fp, "%d,%d,%d", &mapWidth, &mapHeight, &mapDepth) != 3){
        cout << "Erro nas dimensoes do arquivo: " << file << endl;
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
    int index = x + (y * mapWidth) + (z * mapWidth * mapHeight);
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapWidth; i++){
        for (int j = 0; j < mapHeight; ++j){
            auto x = (int)(i * tileSet->GetTileWidth() - cameraX - PARALLAX_FACTOR * Camera::pos.x * layer);
            auto y = (int)(j * tileSet->GetTileHeight() - cameraY - PARALLAX_FACTOR * Camera::pos.y * layer);

            if (IsValidPosition(x, y)) {
                tileSet->RenderTile((unsigned)At(i, j, layer), x, y);
            }
        }
    }
}

bool TileMap::IsValidPosition(int x, int y) const { return x > -tileSet->GetTileWidth() && x < associated.box.w && y > -tileSet->GetTileHeight() && y < associated.box.h; }

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
        RenderLayer(z, (int)(Camera::pos.x), (int)(Camera::pos.y));
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


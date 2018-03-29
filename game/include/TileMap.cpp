//
// Created by edgar on 28/03/18.
//

#include "TileMap.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) {
    Load(file);
    SetTileSet(tileSet);
}

void TileMap::Load(string file) {
    FILE* fp = fopen(file.c_str(), "r");
    if(fp == nullptr){
        std::cout << "Erro ao abrir o arquivo: " << file << std::endl;
        exit(1);
    }
    fscanf(fp, "%d,%d,%d", &mapWidth, &mapHeight, &mapDepth);

}

void TileMap::SetTileSet(TileSet *tileSet) {

}

int &TileMap::At(int x, int y, int z) {
    return <#initializer#>;
}

void TileMap::Render() {

}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {

}

int TileMap::GetWidth() {
    return 0;
}

int TileMap::GetHeight() {

}

int TileMap::GetDepth() {
    return 0;
}

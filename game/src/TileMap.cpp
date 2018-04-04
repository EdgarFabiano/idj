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
    int m = 0, n = 0;
    while(!feof(fp)){
        fscanf(fp, " %d,", &scanned);
        tileMatrix.push_back(scanned - 1);

        if(scanned == 1 && n < mapWidth && m < mapHeight){

            std::cout << "TM1: " << n << " " << m << std::endl;
        }
        n++;
        if(n == mapWidth){
            n = 0;
            m++;
        }
    }
    int i = 0;
    for(i = 0; i < tileMatrix.size(); i++){
        cout << tileMatrix[i] << "\n";
    }

    fclose(fp);
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z) {
    return tileMatrix[0];
}

void TileMap::Render() {

}

void TileMap::Update(float dt) {

}

bool TileMap::Is(string type) {
    return false;
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


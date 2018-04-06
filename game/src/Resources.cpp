//
// Created by edgar on 05/04/18.
//

#include <Game.h>
#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture *Resources::GetImage(string file) {
    if (imageTable.find(file) != imageTable.end()) {
        return (*imageTable.find(file)).second;
    } else {
        auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());
        if(texture == nullptr){
            cout << "Unable to load texture: " << SDL_GetError() << endl;
            exit(1);
        }

        imageTable.insert(make_pair(file, texture));
        return texture;
    }
}

void Resources::ClearImages() {
    for (auto iT = imageTable.begin(); iT != imageTable.end() ; ++iT) {
        SDL_DestroyTexture((*iT).second);
    }
    imageTable.clear();
}

Mix_Music *Resources::GetMusic(string file) {
    if (musicTable.find(file) != musicTable.end()) {
        return (*musicTable.find(file)).second;
    } else {
        auto music = Mix_LoadMUS((ASSETS_PATH + file).c_str());
        if(music == nullptr){
            cout << "Unable to load music: " << SDL_GetError() << endl;
            exit(1);
        }

        musicTable.insert(make_pair(file, music));
        return music;
    }
}

void Resources::ClearMusics() {
    for (auto mT = musicTable.begin(); mT != musicTable.end() ; ++mT) {
        Mix_FreeMusic((*mT).second);
    }
    musicTable.clear();

}

Mix_Chunk *Resources::GetSound(string file) {
    if (soundTable.find(file) != soundTable.end()) {
        return (*soundTable.find(file)).second;
    } else {
        auto chunk = Mix_LoadWAV((ASSETS_PATH + file).c_str());
        if(chunk == nullptr){
            cout << "Unable to load sound: " << SDL_GetError() << endl;
            exit(1);
        }

        soundTable.insert(make_pair(file, chunk));
        return chunk;
    }
}

void Resources::ClearSounds() {
    for (auto sT = soundTable.begin(); sT != soundTable.end(); ++sT) {
        Mix_FreeChunk((*sT).second);
    }
    soundTable.clear();
}


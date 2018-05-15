//
// Created by edgar on 05/04/18.
//

#include <Game.h>
#include "Resources.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;

shared_ptr<SDL_Texture> Resources::GetImage(string file) {
    if (imageTable.find(file) == imageTable.end()) {
        auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());
        if(texture == nullptr){
            cout << "Unable to load texture: " << SDL_GetError() << endl;
            exit(1);
        }

        void (*deleter)(SDL_Texture *) = [] (SDL_Texture *texture) -> void {
                SDL_DestroyTexture(texture);
        };

        auto ptr = shared_ptr<SDL_Texture>(texture, deleter);
        imageTable.emplace(file, ptr);
        return ptr;
    }
    return (*imageTable.find(file)).second;
}

void Resources::ClearImages() {
    for (auto &iT : imageTable) {
        const auto ptr = iT.second;
        if (ptr.unique()) {
            imageTable.erase(iT.first);
        }
    }
    imageTable.clear();
}

shared_ptr<Mix_Music> Resources::GetMusic(string file) {
    if (musicTable.find(file) == musicTable.end()) {
        auto music = Mix_LoadMUS((ASSETS_PATH + file).c_str());
        if(music == nullptr){
            cout << "Unable to load music: " << SDL_GetError() << endl;
            exit(1);
        }

        void (*deleter)(Mix_Music *) = [] (Mix_Music *music) -> void {
            Mix_FreeMusic(music);
        };

        auto ptr = shared_ptr<Mix_Music>(music, deleter);
        musicTable.emplace(file, ptr);
        return ptr;
    }
    return (*musicTable.find(file)).second;
}

void Resources::ClearMusics() {
    for (auto &mT : musicTable) {
        const auto ptr = mT.second;
        if (ptr.unique()) {
            musicTable.erase(mT.first);
        }
    }
    musicTable.clear();
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file) {
    if (soundTable.find(file) == soundTable.end()) {
        auto chunk = Mix_LoadWAV((ASSETS_PATH + file).c_str());
        if(chunk == nullptr){
            cout << "Unable to load sound: " << SDL_GetError() << endl;
            exit(1);
        }

        void (*deleter)(Mix_Chunk *) = [] (Mix_Chunk *chunk) -> void {
            Mix_FreeChunk(chunk);
        };

        auto ptr = shared_ptr<Mix_Chunk>(chunk, deleter);
        soundTable.emplace(file, ptr);
        return ptr;
    }
    return (*soundTable.find(file)).second;
}

void Resources::ClearSounds() {
    for (auto &sT : soundTable) {
        const auto ptr = sT.second;
        if (ptr.unique()) {
            soundTable.erase(sT.first);
        }
    }
    soundTable.clear();
}

shared_ptr<TTF_Font> Resources::GetFont(string file, int size) {
    auto key = file + to_string(size);
    if (fontTable.find(key) == fontTable.end()) {
        auto font = TTF_OpenFont((ASSETS_PATH + file).c_str(), size);
        if(font == nullptr){
            cout << "Unable to load font: " << SDL_GetError() << endl;
            exit(1);
        }

        void (*deleter)(TTF_Font *) = [] (TTF_Font *font) -> void {
            TTF_CloseFont(font);
        };

        auto ptr = shared_ptr<TTF_Font>(font, deleter);
        fontTable.emplace(key, ptr);
        return ptr;
    }
    return (*fontTable.find(key)).second;
}

void Resources::ClearFonts() {
    for (auto &fT : fontTable) {
        const auto ptr = fT.second;
        if (ptr.unique()) {
            fontTable.erase(fT.first);
        }
    }
    fontTable.clear();
}

void Resources::ClearResources() {
    ClearImages();
    ClearMusics();
    ClearSounds();
    ClearFonts();
}


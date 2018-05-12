//
// Created by edgar on 05/04/18.
//

#ifndef RESOURCES_CLASS
#define RESOURCES_CLASS

#include <iostream>
#include <memory>
#include <unordered_map>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;

class Resources {
public:
    static shared_ptr<SDL_Texture> GetImage(string file);
    static void ClearImages();

    static Mix_Music* GetMusic(string file);
    static void ClearMusics();

    static Mix_Chunk* GetSound(string file);
    static void ClearSounds();

    static void ClearResources();

private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, Mix_Music*> musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;

};

#endif //SRC_RESOURCES_H

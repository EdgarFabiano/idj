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
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

using namespace std;

class Resources {
public:
    static shared_ptr<SDL_Texture> GetImage(string file);
    static void ClearImages();

    static shared_ptr<Mix_Music> GetMusic(string file);
    static void ClearMusics();

    static shared_ptr<Mix_Chunk> GetSound(string file);
    static void ClearSounds();

    static shared_ptr<TTF_Font> GetFont(string file, int size);
    static void ClearFonts();

    static void ClearResources();

private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
    static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
    static unordered_map<string, shared_ptr<TTF_Font>> fontTable;

};

#endif //SRC_RESOURCES_H

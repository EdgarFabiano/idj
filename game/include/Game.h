//
// Created by edgar on 16/03/18.
//

#ifndef GAME_CLASS
#define GAME_CLASS

#include <iostream>

#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

#define GAME_NAME "Edgar Fabiano - 14/0019201"
#define SCREEN_SIZE_W 1024
#define SCREEN_SIZE_H 600

#define ASSETS_PATH "assets/"


class Game {

public :
    Game(string title, int width, int height);
    Game(Game&&) = default;
    ~Game();

    void Run();
    SDL_Renderer* GetRenderer ();
    State& GetState ();
    static Game& GetInstance();

private:
    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

};

#endif //SRC_GAME_H

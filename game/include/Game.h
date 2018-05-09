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
#define GAME_WIDTH 1024
#define GAME_HEIGHT 600

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

    float GetDeltaTime();

private:
    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    int frameStart;
    float dt;
    void CalculaDeltaTime();

};

#endif //SRC_GAME_H

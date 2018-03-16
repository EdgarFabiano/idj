//
// Created by edgar on 16/03/18.
//

#ifndef SRC_GAME_H
#define SRC_GAME_H

#include "SDL.h"
#include "State.h"
#include <string>

#define SCREEN_SIZE_W 1024
#define SCREEN_SIZE_H 600


class Game {

public :
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer ();
    State& GetState ();
    static Game& GetInstance();


private:
    Game(std::string title, int width, int height);
    static Game *instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

};


#endif //SRC_GAME_H

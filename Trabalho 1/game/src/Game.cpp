//
// Created by edgar on 16/03/18.
//

#include <iostream>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Game.h"

using namespace std;

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height) {
    if(instance == nullptr) {

        instance = this;

        //Inicializa a SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
            cout << "Unable to SDL_Init: " << SDL_GetError() << endl;
            exit(1);
        }

        //Inicializa as imagens
        int flagsIMG = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
        int initIMG = IMG_Init(flagsIMG);
        if ((initIMG & flagsIMG) != flagsIMG) {
            cout << "Unable to IMG_Init: " << SDL_GetError() << endl;
            exit(1);
        }

        //Inicializa os sons
        int flagsMIX = (/*MIX_INIT_MP3 |*/ MIX_INIT_OGG);
        int initMIX = Mix_Init(flagsMIX);
        if ((initMIX & flagsMIX) != flagsMIX) {
            cout << "Unable to Mix_Init: " << SDL_GetError() << endl;
            exit(1);
        }

        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
            cout << "Unable to Mix_OpenAudio: " << SDL_GetError() << endl;
            exit(1);
        }

        //Determina quantos sons sera capaz de reproduzir simultaneamente. Padrao 8
        //Mix_AllocateChannels(32);

        //Inicializa as fontes
        if (TTF_Init() != 0) {
            cout << "Unable to TTF_Init: " << SDL_GetError() << endl;
            exit(1);
        }

        //Cria a janela
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                                  0/*Flag que lida com o fullscreen*/);
        if (window == nullptr) {
            cout << "Unable to create window: " << SDL_GetError() << endl;
            exit(1);
        }

        //Cria o renderizador
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            cout << "Unable to create renderer: " << SDL_GetError() << endl;
            exit(1);
        }

        //Initialize state
        state = new State();

    }
    else{
        cout << "Instance already exists" << endl;
        exit(1);
    }

}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

}

void Game::Run(){
    State state = GetState();
    while(!GetState().QuitRequested()) {
        state.Update(0);
        state.Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

SDL_Renderer *Game::GetRenderer() {
    return renderer;
}

State &Game::GetState() {
    return *state;
}

Game &Game::GetInstance() {
    if(instance == nullptr)
        return *new Game(GAME_NAME,  SCREEN_SIZE_W, SCREEN_SIZE_H);

    return *instance;
}


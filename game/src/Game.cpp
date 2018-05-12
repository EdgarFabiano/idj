//
// Created by edgar on 16/03/18.
//

#include <iostream>
#include <Resources.h>
#include <InputManager.h>
#include <Collider.h>
#include <Collision.h>

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Game.h"

using namespace std;

Game* Game::instance = nullptr;

Game::Game(string title, int width, int height) : dt(0), frameStart(0) {
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

        //Initialize storedState
        storedState = nullptr;

    }
    else{
        cout << "Instance already exists" << endl;
        exit(1);
    }

}

Game::~Game() {
    //deleting nullptr has no effect
    delete storedState;

    while (!stateStack.empty()) {
        stateStack.pop();
    }

    Resources::ClearResources();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

}

Game &Game::GetInstance() {
    if(instance == nullptr) {
        return *new Game(GAME_NAME, GAME_WIDTH, GAME_HEIGHT);
    }

    return *instance;
}

SDL_Renderer *Game::GetRenderer() {
    return renderer;
}

State &Game::GetCurrentState() {
    return *(unique_ptr<State> &)stateStack.top();
}

void Game::Push(State *state) {
    storedState = state;
}

void Game::Run(){
    if (storedState == nullptr) {
        cout << "Unable to load initial state" << endl;
        exit(1);
    }

    stateStack.emplace(storedState);
    storedState = nullptr;

    GetCurrentState().Start();

    while(!stateStack.empty() && !GetCurrentState().QuitRequested()) {
        State *state = &GetCurrentState();

        if(state->PopRequested()){
            stateStack.pop();
            Resources::ClearResources();
            if(!stateStack.empty()){
                state = &GetCurrentState();
                state->Resume();
            }
        }

        if(storedState){
            if(!stateStack.empty()) {
                state->Pause();
            }
            stateStack.emplace(storedState);
            storedState = nullptr;
            state = &GetCurrentState();
            state->Start();
        }

        CalculateDeltaTime();
        frameStart = SDL_GetTicks();
        InputManager::GetInstance().Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
    Resources::ClearResources();
}

float Game::GetDeltaTime() {
    return dt;
}

void Game::CalculateDeltaTime() {
    int ticks = SDL_GetTicks();
    dt = (ticks - frameStart)/1000.0f;
    frameStart = ticks;
}

//
// Created by edgar on 16/03/18.
//

#include <iostream>
#include <SDL_ttf.h>
#include "../include/Game.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

Game* Game::instance;

Game &Game::GetInstance() {
    if(instance != nullptr)
        return *instance;

    //return new Game("Meu Jogo Maneiro", SCREEN_SIZE_W, SCREEN_SIZE_H);
}

Game::Game(std::string title, int width, int height) {

    if(instance != nullptr){
        std::cout << "Instance already exists" << std::endl;
        exit(1);
    }

    instance = this;

    //Inicializa a SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        std::cout << "Unable to SDL_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Inicializa as imagens
    int flagsIMG = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    int initIMG = IMG_Init(flagsIMG);
    if((initIMG & flagsIMG) != flagsIMG) {
        std::cout << "Unable to IMG_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Inicializa os sons
    int flagsMIX = (/*MIX_INIT_MP3 |*/ MIX_INIT_OGG);
    int initMIX = Mix_Init(flagsMIX);
    if((initMIX & flagsMIX) != flagsMIX) {
        std::cout << "Unable to Mix_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0 ){
        std::cout << "Unable to Mix_OpenAudio: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Determina quantos sons sera capaz de reproduzir simultaneamente. Padrao 8
    //Mix_AllocateChannels(32);

    //Inicializa as fontes
    if(TTF_Init() != 0 ){
        std::cout << "Unable to TTF_Init: " << SDL_GetError() << std::endl;
        exit(1);
    }

    //Cria a janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0/*Flag que lida com o fullscreen*/);
    if(window == nullptr){
        std::cout << "Unable to create window" << SDL_GetError() << std::endl;
        exit(1);
    }

    //Cria o renderizador
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        std::cout << "Unable to create renderer" << SDL_GetError() << std::endl;
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

SDL_Renderer *Game::GetRenderer() {
    return renderer;
}

void Game::Run(){

}


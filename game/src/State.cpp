//
// Created by edgar on 16/03/18.
//

#include <Face.h>
#include <Sound.h>
#include "Sprite.h"
#include "Music.h"
#include "State.h"

State::State()  {
    GameObject *go = new GameObject();
    go->AddComponent(new Sprite(*go, "assets/img/ocean.jpg"));
    objectArray.emplace_back(go);

    LoadAssets();
    quitRequested = false;
    music.Play();
}

State::~State() {
    objectArray.clear();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {
    music.Open("assets/audio/stageState.ogg");
}

void State::Update(float dt) {
    Input();
    for(int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render() {
    for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
        (*it)->Render();
    }
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {

        // Se o evento for quit, setar a flag para terminação
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Se o evento for clique...
        if(event.type == SDL_MOUSEBUTTONDOWN) {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for(int i = objectArray.size() - 1; i >= 0; --i) {
                // Obtem o ponteiro e casta pra Face.
                GameObject* go = (GameObject*) objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
                    Face* face = (Face*)go->GetComponent( "Face" );
                    if ( nullptr != face ) {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if( event.type == SDL_KEYDOWN ) {
            // Se a tecla for ESC, setar a flag de quit
            if( event.key.keysym.sym == SDLK_ESCAPE ) {
                quitRequested = true;
            }
                // Se não, crie um objeto
            else {
                Vec2 objPos = Vec2(200, 0).GetRotated((float)(-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY );
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *go = new GameObject();
    Sprite *sprite = new Sprite(*go, "assets/img/penguinface.png");

    go->box.x = mouseX - go->box.w/2;
    go->box.y = mouseY - go->box.h/2;

    go->AddComponent(sprite);

    go->AddComponent(new Sound(*go, "assets/audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray.emplace_back(go);

}

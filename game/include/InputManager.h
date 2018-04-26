//
// Created by edgar on 06/04/18.
//

#ifndef INPUTMANAGER_CLASS
#define INPUTMANAGER_CLASS

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN

#define A_KEY               SDLK_a
#define D_KEY               SDLK_d
#define W_KEY               SDLK_w
#define S_KEY               SDLK_s

#define SPACE_BAR_KEY       SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE

#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT

#include <unordered_map>
#include <Vec2.h>
#define INCLUDE_SDL
#include "SDL_include.h"

using namespace std;

class InputManager {
public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    Vec2 GetMouse();
    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();

    InputManager();
    ~InputManager();

private:
    bool mouseState[6];

    int mouseUpdate[6];
    unordered_map<int, bool> keyState;

    unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;
    int mouseX;

    int mouseY;
};


#endif //SRC_INPUTMANAGER_H

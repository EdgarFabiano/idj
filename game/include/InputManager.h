//
// Created by edgar on 06/04/18.
//

#ifndef INPUTMANAGER_CLASS
#define INPUTMANAGER_CLASS

#include <unordered_map>

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
    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;
    int mouseY;

};


#endif //SRC_INPUTMANAGER_H

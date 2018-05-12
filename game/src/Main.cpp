#include <TitleState.h>
#include "Game.h"

int main (int argc, char** argv) {
    auto &game = Game::GetInstance();
    game.Push(new TitleState());
    game.Run();

    return 0;
}
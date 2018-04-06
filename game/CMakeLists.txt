cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
link_libraries(SDL2 SDL2_image SDL2_ttf SDL2_mixer)
include_directories(/usr/include/SDL2)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(BEFORE include)
include_directories(BEFORE dep)

add_executable(JOGO src/Main.cpp
        include/SDL_include.h
        src/Game.cpp include/Game.h
        src/State.cpp include/State.h
        src/Sprite.cpp include/Sprite.h
        src/Music.cpp include/Music.h
        src/Rect.cpp include/Rect.h
        src/Vec2.cpp include/Vec2.h
        src/Component.cpp include/Component.h
        src/GameObject.cpp include/GameObject.h
        src/Sound.cpp include/Sound.h
        src/Face.cpp include/Face.h
        src/TileSet.cpp include/TileSet.h
        src/TileMap.cpp include/TileMap.h
        src/Resources.cpp include/Resources.h
        src/InputManager.cpp include/InputManager.h)

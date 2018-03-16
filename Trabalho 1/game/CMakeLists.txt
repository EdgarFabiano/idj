cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
link_libraries(SDL2 SDL2_image SDL2_ttf SDL2_mixer)
include_directories(/usr/include/SDL2)

add_executable(src main.cpp src/Game.cpp include/Game.h src/State.cpp include/State.h)
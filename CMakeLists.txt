cmake_minimum_required(VERSION 3.28)
project(Platformer)

set(CMAKE_CXX_STANDARD 11)

add_executable(Platformer main.cpp
        GameCharacter.cpp
        GameCharacter.h
        constants.h
        frameTime.h
)
target_link_libraries(Platformer sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

cmake_minimum_required(VERSION 3.28)
project(Platformer)

set(CMAKE_CXX_STANDARD 11)

add_executable(Platformer main.cpp
        Hero.cpp
        Hero.h
        constants.h
        frameTime.h
        PhysicsWorld.cpp
        PhysicsWorld.h
        Block.cpp
        Block.h
        BlockGrid.cpp
        BlockGrid.h
        Rectangle.h
        Rectangle.cpp
        Weapon.cpp
        Weapon.h
        Bullet.cpp
        Bullet.h
        GameCharacter.cpp
        GameCharacter.h
        Slime.cpp
        Slime.h
        EnemyContainer.cpp
        EnemyContainer.h
        Enemy.cpp
        Enemy.h
)
target_link_libraries(Platformer sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

cmake_minimum_required(VERSION 3.28)
project(Platformer)

set(CMAKE_CXX_STANDARD 11)

add_executable(Platformer src/main.cpp
        src/Hero.cpp
        includes/Hero.h
        includes/constants.h
        includes/frameTime.h
        src/PhysicsWorld.cpp
        includes/PhysicsWorld.h
        src/Block.cpp
        includes/Block.h
        src/BlockGrid.cpp
        includes/BlockGrid.h
        includes/Rectangle.h
        src/Rectangle.cpp
        src/Weapon.cpp
        includes/Weapon.h
        src/HeroBullet.cpp
        includes/HeroBullet.h
        src/GameCharacter.cpp
        includes/GameCharacter.h
        src/Slime.cpp
        includes/Slime.h
        src/EnemyContainer.cpp
        includes/EnemyContainer.h
        src/Enemy.cpp
        includes/Enemy.h
        src/Plant.cpp
        includes/Plant.h
        src/Bullet.cpp
        includes/Bullet.h
        src/PlantBullet.cpp
        includes/PlantBullet.h
        src/Pig.cpp
        includes/Pig.h
        src/Camera.cpp
        includes/Camera.h
        src/HealthBar.cpp
        includes/HealthBar.h
)
target_link_libraries(Platformer sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

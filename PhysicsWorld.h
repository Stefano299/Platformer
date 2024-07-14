//
// Created by stefano on 7/14/24.
//

#ifndef PLATFORMER_PHYSICSWORLD_H
#define PLATFORMER_PHYSICSWORLD_H


class GameCharacter;
class PhysicsWorld {
private:
    GameCharacter* hero;
    void push(GameCharacter* hero, float v0y) ;

public:
    PhysicsWorld();
    void update();
    void addHero(GameCharacter* hero);
};


#endif //PLATFORMER_PHYSICSWORLD_H

//
// Created by stefano on 7/14/24.
//

#ifndef PLATFORMER_PHYSICSWORLD_H
#define PLATFORMER_PHYSICSWORLD_H

#include<SFML/Graphics.hpp>

class BlockGrid;
class Rectangle;
class GameCharacter;
class PhysicsWorld {
private:
    GameCharacter* hero;
    BlockGrid* grid;
    void fall(int t0);
    bool isColliding(Rectangle* rec1, Rectangle* rec2) const;
public:
    PhysicsWorld();
    void collisionsHandler();
    void update();
    void addHero(GameCharacter* hero);
    void addGrid(BlockGrid* grid);
};


#endif //PLATFORMER_PHYSICSWORLD_H

//
// Created by stefano on 7/14/24.
//

#ifndef PLATFORMER_PHYSICSWORLD_H
#define PLATFORMER_PHYSICSWORLD_H

#include<SFML/Graphics.hpp>

class BlockGrid;
class Rectangle;
class Hero;
class Slime;
class PhysicsWorld {
private:
    Hero* hero;
    BlockGrid* grid;
    Slime* slime;
    void fall();
    bool isColliding(Rectangle* rec1, Rectangle* rec2) const;
    void hitDetection();
    void enemyMovement();
    long int fallingT0;
public:
    PhysicsWorld();
    void collisionsHandler();
    void update();
    void addHero(Hero* hero);
    void addGrid(BlockGrid* grid);
    void addSlime(Slime* slime);
};


#endif //PLATFORMER_PHYSICSWORLD_H

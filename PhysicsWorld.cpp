//
// Created by stefano on 7/14/24.
//

#include "PhysicsWorld.h"
#include"GameCharacter.h"
#include"frameTime.h"
#include"constants.h"
#include"Rectangle.h"
#include"BlockGrid.h"
#include"Block.h"

#include<iostream>




void PhysicsWorld::fall(int t0) {  //Prende il tempo frame
    float time0 = t0*0.01;
    hero->changeY(-time0*time0*GRAVITY);
}

void PhysicsWorld::update() {
    collisionsHandler();
}

void PhysicsWorld::addHero(GameCharacter *hero) {
    this->hero = hero;
}

PhysicsWorld::PhysicsWorld() {
    hero =nullptr;
}

bool PhysicsWorld::isCollidingX(Rectangle* rec1, Rectangle* rec2) const {
    return(rec1->x+rec1->width >rec2->x &&
           rec2->x+rec2->width > rec1->x);
}

bool PhysicsWorld::isCollidingY(Rectangle *rec1, Rectangle *rec2) const {
    return (rec1->y < rec2->y +rec2->height &&
            rec1->y+rec1->height > rec2->y);
}


void PhysicsWorld::addGrid(BlockGrid *grid) {
    this->grid = grid;
}

void PhysicsWorld::collisionsHandler() {
    bool collidedX = false;
    bool collidedY = false;
    for(const auto& it: grid->getBlocks()){
        if(isCollidingX(hero->getRectangle(), it.getRectangle())){
            collidedX = true;
            hero->setCollisionX(true);
            std::cout << "collidingX" << std::endl;
        }
        if(isCollidingY(hero->getRectangle(), it.getRectangle())){
            collidedY = true;
            hero->setCollisionY(true);
            std::cout << "collidingY" << std::endl;
        }
    }
    if(!collidedX)
        hero->setCollisionX(false); //Sennè se colldie con un solo blocco non collide affatto
    if(!collidedY) {
        hero->setCollisionY(false);
    }
}



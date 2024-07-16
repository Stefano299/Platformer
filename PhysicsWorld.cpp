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
    hero->changeY(1);
}

void PhysicsWorld::addHero(GameCharacter *hero) {
    this->hero = hero;
}

PhysicsWorld::PhysicsWorld() {
    hero =nullptr;
}

bool PhysicsWorld::isColliding(Rectangle* rec1, Rectangle* rec2) const {
    return(rec1->x+rec1->width >rec2->x &&
           rec2->x+rec2->width > rec1->x &&
           rec1->y < rec2->y +rec2->height &&
           rec1->y+rec1->height > rec2->y);
}


void PhysicsWorld::addGrid(BlockGrid *grid) {
    this->grid = grid;
}

void PhysicsWorld::collisionsHandler() {
    bool collidedX = false;
    bool collidedY = false;
    Rectangle* heroRec = hero->getRectangle();
    for(const auto& it: grid->getBlocks()) {
        Rectangle* blockRec = it.getRectangle();
        if (isColliding(heroRec, blockRec)) {
            if((heroRec->y+HERO_HEIGTH/2) > blockRec->y) {
                collidedX = true;
                hero->setCollisionX(true);
                std::cout << "collidingX" << std::endl;
            }
            else{
                collidedY = true;
                hero->setCollisionY(true);
                //std::cout << "collidingY" << std::endl;
            }

        }
    }
    if(!collidedX)
        hero->setCollisionX(false); //Sennè se colldie con un solo blocco non collide affatto
    if(!collidedY) {
        hero->setCollisionY(false);
    }
}



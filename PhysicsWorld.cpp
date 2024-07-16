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


void PhysicsWorld::push(GameCharacter* hero,  float v0y)  {
    float dt = frameTime - hero->getTime();
    hero->changeY(dt*dt*GRAVITY*(0.0001)-v0y*dt*(0.01));
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

bool PhysicsWorld::isColliding(Rectangle* rec1, Rectangle* rec2) const {
    return(rec1->x+rec1->width >rec2->x &&
           rec2->x+rec2->width > rec1->x &&
           rec1->y+rec1->height> rec2->y &&
           rec2->y+rec2->height >rec1->y);
}

void PhysicsWorld::addGrid(BlockGrid *grid) {
    this->grid = grid;
}

void PhysicsWorld::collisionsHandler() {
    bool collided = false;
    for(const auto& it: grid->getBlocks()){
        if(isColliding(hero->getRectangle(), it.getRectangle())){
            collided = true;
            hero->setCollision(true);
            std::cout << "colliding" << std::endl;
        }
    }
    if(!collided)
        hero->setCollision(false); //Sennò basta che non collide con uno e non collide
}

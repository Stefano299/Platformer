//
// Created by stefano on 7/14/24.
//

#include "PhysicsWorld.h"

#include"GameCharacter.h"
#include"frameTime.h"
#include"constants.h"

void PhysicsWorld::push(GameCharacter* hero,  float v0y)  {
    float dt = frameTime - hero->getTime();
    hero->changeY(dt*dt*GRAVITY*(0.0001)-v0y*dt*(0.01));
}

void PhysicsWorld::update() {
    if(hero->isJumping()){
        push(hero, 40);
    }
}

void PhysicsWorld::addHero(GameCharacter *hero) {
    this->hero = hero;
}

PhysicsWorld::PhysicsWorld() {
    hero =nullptr;
}

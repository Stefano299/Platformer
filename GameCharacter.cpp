//
// Created by stefano on 7/13/24.
//

#include "GameCharacter.h"
#include"constants.h"
#include"frameTime.h"
#include"PhysicsWorld.h"

#include<iostream>
using namespace std;
GameCharacter::GameCharacter(float x, float y, float speed) {
    jumping = false;
    idleTime = 0;
    runTime = 0;
    this->x = x;
    this->y = y;
    this->speed = speed;
    collidingX = false;
    idleTexture.loadFromFile("../assets/idle.png");
    runTexture.loadFromFile("../assets/run.png");
    sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
    sprite.setOrigin(16, 16);
    sprite.setPosition(x, y);
    animationType = AnimationType::Idle;
    rectangle = new Rectangle (x-12*SCALE_FACTORX,y-12*SCALE_FACTORY, 24*SCALE_FACTORX, 28*SCALE_FACTORY);
}

void GameCharacter::setAnimation() {
    if(animationType == AnimationType::Idle){
        idleAnimation();
    }
    else if(animationType == AnimationType::Run){
        runAnimation();
    }
}

void GameCharacter::timeFlow() {
    if(frameTime%3 ==  0) {
        idleTime++;
    }
    if(frameTime%3 == 0){
        runTime++;
    }
    if(idleTime >= 10)
        idleTime = 0;
    if(runTime >=11)
        runTime=0;
}


void GameCharacter::move(int dx) {
    rectangle->x = x - 12 * SCALE_FACTORX + (float)dx*speed;
    world->update();
    if(!collidingX) {
        if (!jumping)   //Se salta si muove più lentamente orizzontalmente
            x += (float) dx * speed;
        else
            x += (float) dx * (speed / 1.75);
        if (dx == 1) {
            sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
            animationType = AnimationType::Run;
            cout << "right" << endl;
        } else if (dx == -1) {
            sprite.setScale(-SCALE_FACTORX, SCALE_FACTORY);
            animationType = AnimationType::Run;
            cout << "left" << endl;
        } else
            animationType = AnimationType::Idle;
        sprite.setPosition(x, y);
    }
    else
        rectangle->x = x - 12 * SCALE_FACTORX;
}


void GameCharacter::draw(sf::RenderWindow& window) {
    timeFlow();
    setAnimation();
    if(jumping) {
        changeY(-17);  //Lo fa saltare
    }
    sprite.setPosition(x,y);
    window.draw(sprite);
    rectangle->draw(window);
}

void GameCharacter::idleAnimation()  {
    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect (idleTime * 32, 0, 32, 32));
}

void GameCharacter::runAnimation() {
    sprite.setTexture(runTexture);
    sprite.setTextureRect(sf::IntRect (runTime * 32, 0, 32, 32));
}


void GameCharacter::changeY(float dy) {
    rectangle->y+=dy;
    world->collisionsHandler();
    if(!collidingY) {
        y += dy;
        cout << dy << endl;
    }
    else {
        jumping = false;
        rectangle->y -= dy;
    }
}

float GameCharacter::getX() const {
    return x;
}

float GameCharacter::getY() const {
    return y;
}

float GameCharacter::getSpeed() const {
    return speed;
}


void GameCharacter::jump() {
    jumping = true;
}


GameCharacter::~GameCharacter() {
    delete rectangle;
}

Rectangle *GameCharacter::getRectangle() const {
    return rectangle;
}

void GameCharacter::setCollisionX(bool c) {
    collidingX = c;
}

void GameCharacter::setPhysicsWorld(PhysicsWorld *w) {
    world = w;
}

void GameCharacter::setCollisionY(bool c) {
    collidingY = c;
}

bool GameCharacter::isCollidingY() const {
    return collidingY;
}










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
    deltaY = 0;
    collidingX = false;
    idleTexture.loadFromFile("../assets/idle.png");
    runTexture.loadFromFile("../assets/run.png");
    jumpTexture.loadFromFile("../assets/jump.png");
    fallTexture.loadFromFile("../assets/fall.png");
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
    else if(animationType == AnimationType::Run) {
        runAnimation();
    }
    else if(animationType == AnimationType::Fall){
        fallAnimation();
    }
    else if(animationType == AnimationType::Jump)
        jumpAnimation();
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
        } else if (dx == -1) {
            sprite.setScale(-SCALE_FACTORX, SCALE_FACTORY);
            animationType = AnimationType::Run;
        } else
            animationType = AnimationType::Idle;
        sprite.setPosition(x, y);
    }
    else
        rectangle->x = x - 12 * SCALE_FACTORX;
}


void GameCharacter::draw(sf::RenderWindow& window) {
    timeFlow();
    if(jumping) {
        changeY(-17);  //Lo fa saltare
    }
    if(deltaY>0)  //Se sta andando in alto metto l'animazione jump,sennò quella che cade
        animationType = AnimationType::Fall;
    else if(deltaY < 0)
        animationType = AnimationType::Jump;
    deltaY= 0;
    setAnimation();
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

void GameCharacter::jumpAnimation() {
    sprite.setTexture(jumpTexture);
    sprite.setTextureRect(sf::IntRect (0, 0, 32, 32));
}

void GameCharacter::fallAnimation() {
    sprite.setTexture(fallTexture);
    sprite.setTextureRect(sf::IntRect (0, 0, 32, 32));
}


void GameCharacter::changeY(float dy) {
    rectangle->y+=dy;
    world->collisionsHandler();
    if(!collidingY) {
        deltaY += dy;
        y += dy;
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
    if(deltaY == 0) //Se sta cadendo o saltando non pà (ri)saltare
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

void GameCharacter::stopJumping() {
    jumping = false;
}

float GameCharacter::getDeltaY() const {
    return deltaY;
}









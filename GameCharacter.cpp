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
    idleTexture.loadFromFile("../assets/idle.png");
    runTexture.loadFromFile("../assets/run.png");
    sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
    sprite.setOrigin(16, 16);
    sprite.setPosition(x, y);
    animationType = AnimationType::Idle;
    rectangle = new Rectangle (x-16*SCALE_FACTORX,y-16*SCALE_FACTORY, 32*SCALE_FACTORX, 32*SCALE_FACTORY);
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
    if(!jumping)   //Se salta si muove più lentamente orizzontalmente
        x += (float)dx*speed;
    else
        x+=(float)dx*(speed/1.75);
    if(dx==1) {
        sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
        animationType = AnimationType::Run;
        cout << "right" << endl;
    }
    else if(dx ==-1){
        sprite.setScale(-SCALE_FACTORX, SCALE_FACTORY);
        animationType = AnimationType::Run;
        cout << "left" <<  endl;
    }
    else
        animationType = AnimationType::Idle;
    rectangle->x = x-16*SCALE_FACTORX;
    rectangle->y = y-16*SCALE_FACTORY;
    sprite.setPosition(x,y);
}

void GameCharacter::draw(sf::RenderWindow& window) {
    timeFlow();
    setAnimation();
    window.draw(sprite);
}

void GameCharacter::idleAnimation()  {
    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect (idleTime * 32, 0, 32, 32));
}

void GameCharacter::runAnimation() {
    sprite.setTexture(runTexture);
    sprite.setTextureRect(sf::IntRect (runTime * 32, 0, 32, 32));
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

void GameCharacter::changeY(float dy) {
    y+=dy;
    if(y>=SCREEN_HEIGTH)
        jumping = false;
}

void GameCharacter::jump() {
    jumping = true;
    initialTime = frameTime;
}

int GameCharacter::getTime() const {
    return initialTime;
}

bool GameCharacter::isJumping() const {
    return jumping;
}

GameCharacter::~GameCharacter() {
    delete rectangle;
}

Rectangle *GameCharacter::getRectangle() const {
    return rectangle;
}










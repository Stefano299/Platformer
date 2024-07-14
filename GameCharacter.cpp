//
// Created by stefano on 7/13/24.
//

#include "GameCharacter.h"
#include"constants.h"
#include"frameTime.h"
#include<iostream>
using namespace std;
GameCharacter::GameCharacter(float x, float y, float speed) {
    idleTime = 0;
    this->x = x;
    this->y = y;
    this->speed = speed;
    idleTexture.loadFromFile("../assets/idle.png");
    runTexture.loadFromFile("../assets/run.png");
    float scaleX = ((float)SCREEN_WIDTH/1920)*3;
    float scaleY = ((float)SCREEN_HEIGTH / 1200) * 3;
    sprite.setScale(scaleX, scaleY);
    sprite.setOrigin(16, 16);
    sprite.setPosition(x, y);
    animationType = AnimationType::Idle;
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
    x += (float)dx*speed;
    float scaleX = ((float)SCREEN_WIDTH/1920)*3;
    float scaleY = ((float)SCREEN_HEIGTH / 1200) * 3;
    if(dx==1) {
        sprite.setScale(scaleX, scaleY);
        animationType = AnimationType::Run;
        cout << "right" << endl;
    }
    else if(dx ==-1){
        sprite.setScale(-scaleX, scaleY);
        animationType = AnimationType::Run;
        cout << "left" <<  endl;
    }
    else
        animationType = AnimationType::Idle;
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









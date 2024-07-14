//
// Created by stefano on 7/13/24.
//

#include "GameCharacter.h"
#include"constants.h"
#include"frameTime.h"

GameCharacter::GameCharacter(float x, float y, float speed) {
    animTime = 0;
    this->x = x;
    this->y = y;
    this->speed = speed;
    idleTexture.loadFromFile("../assets/idle.png");
    runTexture.loadFromFile("../assets/run.png");
    sprite.scale(((float)SCREEN_WIDTH/1920)*3, ((float)SCREE_HEIGTH/1200)*3);
    sprite.setPosition(x, y);
    animationType = AnimationType::Idle;
}

void GameCharacter::setAnimation() {
    if(animationType== AnimationType::Idle)
        idleAnimation();
}

void GameCharacter::timeFlow() {
    if(frameTime%3 ==  0)
        animTime++;
    if(animTime >= 10)
        animTime = 0;
}


void GameCharacter::move(int dx, int dy) {
    x += (float)dx*speed;
    y += (float)dy*speed;
    sprite.setPosition(x,y);
}

void GameCharacter::draw(sf::RenderWindow& window) {
    timeFlow();
    setAnimation();
    window.draw(sprite);
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

void GameCharacter::idleAnimation()  {
    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect (animTime*32, 0, 32, 32));
}







//
// Created by stefano on 7/17/24.
//

#include "GameCharacter.h"

GameCharacter::GameCharacter(float x, float y, float speed, int hp) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->hp = hp;
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

Rectangle *GameCharacter::getRectangle() const {
    return rectangle;
}

GameCharacter::~GameCharacter() {
    delete rectangle;
}

int GameCharacter::getHp() const {
    return hp;
}


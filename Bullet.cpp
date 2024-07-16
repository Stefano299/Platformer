//
// Created by stefano on 7/16/24.
//

#include <iostream>

#include "Bullet.h"
#include"constants.h"
#include"Rectangle.h"
#include"frameTime.h"

Bullet::Bullet(float x, float y, float s, int d):x(x),y(y),speed(s),direction(d),animIndex(0) {
    texture.loadFromFile("../assets/bullet.png");
    sprite.setPosition(x,y);
    sprite.setScale(1.3, 1.3);
    rectangle = new Rectangle(x,y,BULLET_WIDTH, BULLET_HEIGTH);
}

Bullet::~Bullet() {
    delete rectangle;
}

void Bullet::move() {
    x+=(float)direction*speed;
    sprite.setPosition(x, y);
    rectangle->x = x;
}

void Bullet::draw(sf::RenderWindow &window) {
    nextIndex();
    updateAnimation();
    move();
    window.draw(sprite);
}

void Bullet::nextIndex() {
    if(frameTime%2 == 0) {
        if(animIndex< 7)
            animIndex++;
        else
            animIndex = 0;
    }
}

void Bullet::updateAnimation() {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect (animIndex * 38, 0, 38, 38));
}

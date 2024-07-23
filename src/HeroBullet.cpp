//
// Created by stefano on 7/16/24.
//

#include <iostream>

#include "../includes/HeroBullet.h"
#include"../includes/constants.h"
#include"../includes/Rectangle.h"
#include"../includes/frameTime.h"

HeroBullet::HeroBullet(float x, float y, float s, int d): Bullet(x,y,s,d) {
    animIndex = 0;
    texture.loadFromFile("../assets/bullet.png");
    sprite.setPosition(x,y);
    sprite.setScale(1.3, 1.3);
    rectangle = new Rectangle(x,y,BULLET_WIDTH, BULLET_HEIGTH);
}

void HeroBullet::draw(sf::RenderWindow &window) {
    nextIndex();
    updateAnimation();
    move();
    window.draw(sprite);
}

void HeroBullet::nextIndex() {
    if(frameTime%2 == 0) {
        if(animIndex< 7)
            animIndex++;
        else
            animIndex = 0;
    }
}

void HeroBullet::updateAnimation() {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect (animIndex * 38, 0, 38, 38));
}

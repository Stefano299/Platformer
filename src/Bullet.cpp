//
// Created by stefano on 7/18/24.
//

#include "../includes/Bullet.h"
#include "../includes/Rectangle.h"

Bullet::~Bullet() {
    delete rectangle;
}

void Bullet::move() {
    x+=(float)direction*speed;
    sprite.setPosition(x, y);
    rectangle->x = x;
}

Rectangle* Bullet::getRectangle() const {
    return rectangle;
}

Bullet::Bullet(float x, float y, float s, int d):x(x), y(y), speed(s), direction(d){}

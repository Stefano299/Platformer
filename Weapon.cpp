//
// Created by stefano on 7/16/24.
//

#include "Weapon.h"
#include"Bullet.h"

void Weapon::shoot(float x, float y, int dir) {
    bullets.push_back(new Bullet(x,y,15, dir));
}

const std::vector<Bullet *> &Weapon::getBullets() const {
    return bullets;
}

Weapon::~Weapon() {
    for(auto it:bullets)
        delete it;
}

void Weapon::draw(sf::RenderWindow &window) const {
    for(auto it: bullets)
        it->draw(window);
}

void Weapon::deleteBullet(Bullet* bullet) {
    auto it = std::find(bullets.begin(), bullets.end(), bullet);
    bullets.erase(it);
    delete bullet;
}

Weapon::Weapon() {
    damage = 5;
}

int Weapon::getDamage() const {
    return damage;
}

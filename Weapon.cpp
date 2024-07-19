//
// Created by stefano on 7/16/24.
//

#include "Weapon.h"
#include"HeroBullet.h"
#include"PlantBullet.h"

Weapon::Weapon() {
    damage = 0;
}

void Weapon::shoot(float x, float y, int dir) {
    if(type == WeaponType::Hero) {
        bullets.push_back(new HeroBullet(x, y, 15, dir));
    }
    else if(type == WeaponType::Plant){
        bullets.push_back(new PlantBullet(x, y, 20, dir));
    }
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


int Weapon::getDamage() const {
    return damage;
}

void Weapon::setType(WeaponType type) {
    this->type = type;
    if(type == WeaponType::Hero)
        damage = 10;
    else
        damage = 5;
}


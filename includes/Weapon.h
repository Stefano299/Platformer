//
// Created by stefano on 7/16/24.
//

#ifndef PLATFORMER_WEAPON_H
#define PLATFORMER_WEAPON_H

#include<vector>
#include<SFML/Graphics.hpp>

enum class WeaponType{
    Hero,
    Plant
};

class Bullet;
class Weapon {
private:
    std::vector<Bullet*> bullets;
    WeaponType type;
    int damage;
public:
    Weapon();
    void setType(WeaponType type);
    void shoot(float x, float y, int dir);
    const std::vector<Bullet*>& getBullets() const;
    void deleteBullet(Bullet* bullet);
    void draw(sf::RenderWindow& window) const;
    int getDamage() const;
    ~Weapon();
};


#endif //PLATFORMER_WEAPON_H

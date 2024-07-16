//
// Created by stefano on 7/16/24.
//

#ifndef PLATFORMER_WEAPON_H
#define PLATFORMER_WEAPON_H

#include<vector>
#include<SFML/Graphics.hpp>

class Bullet;
class Weapon {
private:
    std::vector<Bullet*> bullets;
public:
    Weapon() = default;
    void shoot(float x, float y, int dir);
    const std::vector<Bullet*>& getBullets() const;
    void deleteBullet(Bullet* bullet);
    void draw(sf::RenderWindow& window) const;
    ~Weapon();
};


#endif //PLATFORMER_WEAPON_H

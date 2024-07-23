//
// Created by stefano on 7/16/24.
//

#ifndef PLATFORMER_HEROBULLET_H
#define PLATFORMER_HEROBULLET_H

#include<SFML/Graphics.hpp>
#include"Bullet.h"

class HeroBullet: public Bullet {
private:
    int animIndex;
    void nextIndex();
    void updateAnimation();
public:
    HeroBullet(float x, float y, float s, int d);
    void draw(sf::RenderWindow& window) override;
};


#endif //PLATFORMER_HEROBULLET_H

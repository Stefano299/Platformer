//
// Created by stefano on 7/18/24.
//

#ifndef PLATFORMER_PLANTBULLET_H
#define PLATFORMER_PLANTBULLET_H

#include"Bullet.h"

class PlantBullet:public Bullet {
public:
    PlantBullet(float x, float y, float s, int d);
    void draw(sf::RenderWindow& window) override;
};


#endif //PLATFORMER_PLANTBULLET_H

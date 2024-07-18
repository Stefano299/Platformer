//
// Created by stefano on 7/17/24.
//

#ifndef PLATFORMER_SLIME_H
#define PLATFORMER_SLIME_H

#include"Enemy.h"

enum class SlimeAnimationType{
    Run,
    Hit
};

class Slime:public Enemy {
private:
    void hitAnimation();
    void runAnimation();
    void timeFlow();
    void setAnimation();
    sf::Texture hitTexture;
    sf::Texture runTexture;
    SlimeAnimationType animationType;
    int hitIndex;
    int runIndex;
public:
    Slime(float x, float y, float speed, int hp);
    void draw(sf::RenderWindow& window) override;
    void hit(int dmg) override;
};


#endif //PLATFORMER_SLIME_H

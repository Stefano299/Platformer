//
// Created by stefano on 7/17/24.
//

#ifndef PLATFORMER_SLIME_H
#define PLATFORMER_SLIME_H

#include"GameCharacter.h"

enum class SlimeAnimationType{
    Run,
    Hit
};

class Slime:public GameCharacter {
private:
    void hitAnimation();
    void runAnimation();
    void timeFlow();
    void setAnimation();
    sf::Texture hitTexture;
    sf::Texture runTexture;
    SlimeAnimationType animationType;
    int hp;
    int hitIndex;
    int runIndex;
    int direction;
public:
    Slime(float x, float y, float speed);
    void move(int dx) override;
    void draw(sf::RenderWindow& window) override;
    int getDirection() const;
    void changeDirection();
    void hit(int dmg);
};


#endif //PLATFORMER_SLIME_H

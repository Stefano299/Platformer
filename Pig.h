//
// Created by stefano on 7/19/24.
//

#ifndef PLATFORMER_PIG_H
#define PLATFORMER_PIG_H

#include"Enemy.h"

enum class PigAnimationType{
    Walk,
    Run,
    Hit
};

class Pig: public Enemy {
private:
    void hitAnimation();
    void walkAnimation();
    void runAnimation();
    void timeFlow();
    void setAnimation();
    sf::Texture hitTexture;
    sf::Texture walkTexture;
    sf::Texture runTexture;
    PigAnimationType animationType;
    int hitIndex;
    int runIndex;
    int walkIndex;
public:
    Pig(float x, float y, float speed, int hp);
    void draw(sf::RenderWindow& window) override;
    void hit(int dmg) override;
};


#endif //PLATFORMER_PIG_H

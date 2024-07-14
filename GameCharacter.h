//
// Created by stefano on 7/13/24.
//

#ifndef PLATFORMER_GAMECHARACTER_H
#define PLATFORMER_GAMECHARACTER_H

#include<iostream>
#include<SFML/Graphics.hpp>

enum class AnimationType{
    Idle,
    Run,
    Jump,
    Fall
};

class GameCharacter {
private:
    void setAnimation();
    void idleAnimation();
    void runAnimation();
    void timeFlow();
    int idleTime;
    int runTime;
    float x;
    float y;
    float speed;
    AnimationType animationType;
    sf::Sprite sprite;
    sf::Texture idleTexture;
    sf::Texture runTexture;
public:
    GameCharacter(float x, float y, float speed);
    void move(int dx);
    void draw(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
    float getSpeed() const;
};


#endif //PLATFORMER_GAMECHARACTER_H

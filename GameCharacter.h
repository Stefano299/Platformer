//
// Created by stefano on 7/13/24.
//

#ifndef PLATFORMER_GAMECHARACTER_H
#define PLATFORMER_GAMECHARACTER_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include"Rectangle.h"

enum class AnimationType{
    Idle,
    Run,
    Jump,
    Fall
};

class PhysicsWorld;
class GameCharacter {
private:
    void setAnimation();
    void idleAnimation();
    void runAnimation();
    void timeFlow();
    bool jumping;
    int idleTime;
    int runTime;
    float x;
    float y;
    float speed;
    bool collidingX;
    bool collidingY;
    Rectangle* rectangle;
    AnimationType animationType;
    sf::Sprite sprite;
    sf::Texture idleTexture;
    sf::Texture runTexture;
    PhysicsWorld* world;
public:
    GameCharacter(float x, float y, float speed);
    void move(int dx);
    void draw(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
    float getSpeed() const;
    void jump();
    void changeY(float dy);
    void setCollisionX(bool c);
    void setCollisionY(bool c);
    bool isCollidingY() const;
    void setPhysicsWorld(PhysicsWorld* w);
    Rectangle* getRectangle() const;
    ~GameCharacter();
};


#endif //PLATFORMER_GAMECHARACTER_H

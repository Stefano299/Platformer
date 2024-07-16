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
    void jumpAnimation();
    void fallAnimation();
    void timeFlow();
    bool jumping;
    int idleTime;
    int runTime;
    float x;
    float y;
    float speed;
    bool collidingX;
    bool collidingY;
    float deltaY; //Mi serve per le animazioni di salto e caduta
    Rectangle* rectangle;
    AnimationType animationType;
    sf::Sprite sprite;
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture jumpTexture;
    sf::Texture fallTexture;
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
    void stopJumping();
    float getDeltaY() const;
    void setPhysicsWorld(PhysicsWorld* w);
    Rectangle* getRectangle() const;
    ~GameCharacter();
};


#endif //PLATFORMER_GAMECHARACTER_H

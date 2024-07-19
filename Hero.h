//
// Created by stefano on 7/13/24.
//

#ifndef PLATFORMER_HERO_H
#define PLATFORMER_HERO_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include"Rectangle.h"
#include "Weapon.h"
#include"GameCharacter.h"

enum class AnimationType{
    Idle,
    Run,
    Jump,
    Fall
};

class PhysicsWorld;
class Hero: public GameCharacter {
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
    bool collidingX;
    bool collidingY;
    float deltaY; //Mi serve per le animazioni di salto e caduta
    int shootTime;
    AnimationType animationType;
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture jumpTexture;
    sf::Texture fallTexture;
    PhysicsWorld* world;
    Weapon weapon;
public:
    Hero(float x, float y, float speed);
    void move(int dx) override;
    void draw(sf::RenderWindow& window) override;
    void jump();
    void changeY(float dy);
    void setCollisionX(bool c);
    void setCollisionY(bool c);
    void stopJumping();
    float getDeltaY() const;
    void shoot();
    void setPhysicsWorld(PhysicsWorld* w);
    const Weapon& getWeapon() const;
};


#endif //PLATFORMER_HERO_H
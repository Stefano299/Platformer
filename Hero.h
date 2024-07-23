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

class Camera;
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
    int collidingTime; //Per quando colpisce un nemico
    bool collidingEnemy;
    int directionX;
    AnimationType animationType;
    sf::Texture idleTexture;
    sf::Texture runTexture;
    sf::Texture jumpTexture;
    sf::Texture fallTexture;
    PhysicsWorld* world;
    Camera* camera;
    Weapon weapon;
public:
    Hero(float x, float y, float speed, int hp);
    Camera* getCamera() const;
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
    void hit(int dmg, bool collided = false); //Nascono hit di gamecharacter, voglio divrsi  argomenti
    void drawHealthBar(sf::RenderWindow& window) const; //Per disegnarla dopo tutto, così non sta mai dietro niente
    int getDirectionX() const;
    bool getCollidingEnemy() const;
    AnimationType getAnimationType() const;
    ~Hero() override;
};


#endif //PLATFORMER_HERO_H

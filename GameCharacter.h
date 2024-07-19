//
// Created by stefano on 7/17/24.
//

#ifndef PLATFORMER_GAMECHARACTER_H
#define PLATFORMER_GAMECHARACTER_H

#include<SFML/Graphics.hpp>
#include"Rectangle.h"


class Rectangle;
class GameCharacter {
protected:
    float x;
    float y;
    float speed;
    Rectangle* rectangle;
    sf::Sprite sprite;
    int hp;
public:
    GameCharacter(float x, float y, float speed, int hp = 0);
    float getX() const;
    float getY() const;
    float getSpeed() const;
    int getHp() const;
    Rectangle* getRectangle() const;
    virtual void move(int dx) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void hit(int dmg);
    virtual ~GameCharacter();
};


#endif //PLATFORMER_GAMECHARACTER_H

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
public:
    GameCharacter(float x, float y, float speed);
    float getX() const;
    float getY() const;
    float getSpeed() const;
    Rectangle* getRectangle() const;
    virtual void move(int dx) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~GameCharacter();
};


#endif //PLATFORMER_GAMECHARACTER_H

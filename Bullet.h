//
// Created by stefano on 7/18/24.
//

#ifndef PLATFORMER_BULLET_H
#define PLATFORMER_BULLET_H

#include<SFML/Graphics.hpp>

class Rectangle;
class Bullet {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    Rectangle* rectangle;
    float x;
    float y;
    float speed;
    int direction;
public:
    Bullet(float x, float y, float s, int d);
    virtual void move();
    virtual void draw(sf::RenderWindow& window) = 0;
    Rectangle* getRectangle() const;
    virtual ~Bullet();
};


#endif //PLATFORMER_BULLET_H

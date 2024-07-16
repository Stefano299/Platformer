//
// Created by stefano on 7/16/24.
//

#ifndef PLATFORMER_BULLET_H
#define PLATFORMER_BULLET_H

#include<SFML/Graphics.hpp>

class Rectangle;
class Bullet {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    Rectangle* rectangle;
    float x;
    float y;
    float speed;
    int animIndex;
    int direction;
    void nextIndex();
    void updateAnimation();
public:
    Bullet(float x, float y, float s, int d);
    void move();
    void draw(sf::RenderWindow& window);
    ~Bullet();
};


#endif //PLATFORMER_BULLET_H

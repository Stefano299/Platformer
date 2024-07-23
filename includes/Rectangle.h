//
// Created by stefano on 7/15/24.
//

#ifndef PLATFORMER_RECTANGLE_H
#define PLATFORMER_RECTANGLE_H

#include<SFML/Graphics.hpp>

struct Rectangle {
public:
    float x;
    float y;
    float width;
    float height;
    sf::RectangleShape shape;
public:
    Rectangle(float x, float y, float w, float h);
    void draw(sf::RenderWindow& window);
};


#endif //PLATFORMER_RECTANGLE_H

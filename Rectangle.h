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
    Rectangle(float x, float y, float w, float h):x(x), y(y), width(w), height(h){
        shape.setSize(sf::Vector2f (w, h));
        shape.setPosition(x,y);
        shape.setFillColor(sf::Color(0,150,0,100));
    }
    void draw(sf::RenderWindow& window){
        shape.setPosition(x,y);
        window.draw(shape);
    }
};


#endif //PLATFORMER_RECTANGLE_H

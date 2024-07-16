//
// Created by stefano on 7/16/24.
//

#include"Rectangle.h"

Rectangle::Rectangle(float x, float y, float w, float h):x(x), y(y), width(w), height(h){
    shape.setSize(sf::Vector2f (w, h));
    shape.setPosition(x,y);
    shape.setFillColor(sf::Color(0,150,0,100));
}
void Rectangle::draw(sf::RenderWindow& window){
    shape.setPosition(x,y);
    window.draw(shape);
}
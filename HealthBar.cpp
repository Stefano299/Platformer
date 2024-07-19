//
// Created by stefano on 7/19/24.
//

#include "HealthBar.h"
#include<iostream>

HealthBar::HealthBar(float x, float y, float width, float heigth) {
    this->x = x;
    this->y = y;
    this->heigth = heigth;
    this->width = width;
    bar.setSize(sf::Vector2f (width, heigth));
    bar.setPosition(x, y);  //Considero lo spessore del bordo (10 px)
    bar.setFillColor(sf::Color::Green);
    border.setSize(sf::Vector2f (width-10,heigth));
    border.setPosition(x,y);
    border.setFillColor(sf::Color(0, 0, 0, 0)); //Il bordo è un rettanglolo trasparente
    border.setOutlineThickness(10);
    border.setOutlineColor(sf::Color::Black);
}

void HealthBar::draw(sf::RenderWindow &window) {
    window.draw(bar);
    window.draw(border);
}

void HealthBar::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    bar.setPosition(x,y);
    border.setPosition(x,y);
}

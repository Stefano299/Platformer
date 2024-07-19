//
// Created by stefano on 7/19/24.
//

#ifndef PLATFORMER_HEALTHBAR_H
#define PLATFORMER_HEALTHBAR_H

#include<SFML/Graphics.hpp>

class HealthBar {
private:
    float x;
    float y;
    float heigth;
    float width;
    sf::RectangleShape border;
    sf::RectangleShape bar;
public:
    HealthBar(float x, float y, float width, float heigth);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
};

#endif //PLATFORMER_HEALTHBAR_H

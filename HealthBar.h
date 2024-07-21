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
    float maxWidth;
    sf::RectangleShape border;
    sf::RectangleShape bar;
    sf::Texture heartTxt; //Il cuoricino disegnato a sinistra della barra
    sf::Sprite heartSpr;
public:
    HealthBar(float x, float y, float width, float heigth);
    void draw(sf::RenderWindow& window)const;
    void setPosition(float x, float y);
    float getX() const;
    float getY() const;
    void update(int hp, int maxHealth);
};

#endif //PLATFORMER_HEALTHBAR_H

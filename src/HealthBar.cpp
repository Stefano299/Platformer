//
// Created by stefano on 7/19/24.
//

#include "../includes/HealthBar.h"
#include<iostream>

HealthBar::HealthBar(float x, float y, float width, float heigth) {
    this->x = x;
    this->y = y;
    this->heigth = heigth;
    this->width = width;
    maxWidth = width; //La larghezza iniziale che non diminuisce
    bar.setSize(sf::Vector2f (width, heigth));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(22,201,88)); //la barra quando è piena è verde
    border.setSize(sf::Vector2f (width,heigth));
    border.setPosition(x,y);
    border.setFillColor(sf::Color(0, 0, 0, 0)); //Il bordo è un rettanglolo trasparente
    border.setOutlineThickness(7);
    border.setOutlineColor(sf::Color::Black);
    heartTxt.loadFromFile("../assets/heart.png");
    heartSpr.setTexture(heartTxt);
    heartSpr.setScale(0.5, 0.5);
    heartSpr.setPosition(x-145, y-10);
}

void HealthBar::draw(sf::RenderWindow &window) const{
    window.draw(bar);
    window.draw(border);
    window.draw(heartSpr);
}

void HealthBar::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    bar.setPosition(x,y);
    border.setPosition(x,y);
    heartSpr.setPosition(x-145, y-10);
}

void HealthBar::update(int hp, int maxHealth) {
    //hp:maxHealth=x:maxWidth, faccio una proporzione
    width = ((float)hp/maxHealth)*maxWidth;
    if(width < 0)
        width = 0; //sennò va negativa
    bar.setSize(sf::Vector2f (width,heigth)); //Devo aggiornare la dimensione
    if((float)hp/maxHealth <= 0.3)
        bar.setFillColor(sf::Color(216,12,39));
    else if((float)hp/maxHealth <= 0.6)
        bar.setFillColor(sf::Color(255,128,0));
}

float HealthBar::getX() const {
    return x;
}

float HealthBar::getY() const {
    return y;
}

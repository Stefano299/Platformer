//
// Created by stefano on 7/19/24.
//

#include <iostream>
#include "Camera.h"
#include"constants.h"

Camera::Camera(float width, float heigth, float speed):width(width), heigth(heigth),speed(speed) {
    view.setSize(width, heigth);
    x = width/2;
    y = heigth/2;
    view.setCenter(x, y);
    backgroundTxt.loadFromFile("../assets/background.jpg");
    backgroundSpr.setTexture(backgroundTxt);
    backgroundSpr.setOrigin(1920/2,1200/2); //Il bacground è 1920x1200, metto quindi l'orgine al centro
    backgroundSpr.scale((float)SCREEN_WIDTH/1920, (float)SCREEN_HEIGTH / 1200);
    backgroundSpr.setPosition(x,y);
}

void Camera::setView(sf::RenderWindow &window) const{
    window.setView(view);
}

float Camera::getX() const {
    return x;
}

float Camera::getY() const {
    return y;
}

void Camera::arrowsMove(sf::RenderWindow& window) {
    int dx = 0;
    int dy = 0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        dy = -1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        dy = +1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        dx=+1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        dx=-1;
    x += dx*speed;
    y += dy*speed;
    view.setCenter(x,y);
    backgroundSpr.setPosition(x,y);
    window.setView(view);
}

void Camera::drawBackground(sf::RenderWindow &window) {
    window.draw(backgroundSpr);
}

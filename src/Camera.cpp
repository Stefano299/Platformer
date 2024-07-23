//
// Created by stefano on 7/19/24.
//

#include <iostream>
#include "../includes/Camera.h"
#include"../includes/constants.h"
#include "../includes/HealthBar.h"
#include"../includes/frameTime.h"

Camera::Camera(float width, float heigth, float speed):width(width), heigth(heigth),speed(speed), gameOverIndex(0) {
    view.setSize(width, heigth);
    x = width/2;
    y = heigth/2;
    healthBar = new HealthBar(x-width/2+160, y-heigth/2+100, 800, 80);
    view.setCenter(x, y);
    backgroundTxt.loadFromFile("../assets/background.jpg");
    gameoverTxt.loadFromFile("../assets/gameover.png");
    gameoverSpr.setTexture(gameoverTxt);
    gameoverSpr.setOrigin(650.f, 650.f);
    gameoverSpr.setScale(0,0); //Voglio venga mostrato solo quando si muore
    gameoverSpr.setPosition(x,y);
    backgroundSpr.setTexture(backgroundTxt);
    backgroundSpr.setOrigin(1920/2,1200/2); //Il bacground è 1920x1200, metto quindi l'orgine al centro
    backgroundSpr.scale((float)SCREEN_WIDTH/1920, (float)SCREEN_HEIGTH / 1200);
    backgroundSpr.setPosition(x,y);
}

void Camera::gameOver() {
    if(frameTime % 1 == 0 && gameOverIndex <= 100)
        gameOverIndex++; //inizialmente ha una grandezza di 0, quindi non esiste
    gameoverSpr.setScale(0.014*(float)gameOverIndex, 0.014*(float)gameOverIndex);
}


float Camera::getX() const {
    return x;
}

float Camera::getY() const {
    return y;
}

void Camera::arrowsMove() {
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
    x += dx*speed*2; //Se la  muovo con le freccette voglio vada più veloce
    y += dy*speed*2;
    view.setCenter(x,y);
    backgroundSpr.setPosition(x,y);
    healthBar->setPosition(x - width / 2 + 160, y - heigth / 2 + 100);
}

void Camera::update(sf::RenderWindow &window) {
    window.setView(view);
    window.draw(backgroundSpr);
    gameoverSpr.setPosition(x,y);
    //healthBar->draw(window);
}

void Camera::move(int dx, int dy) {
    x+=dx*speed;
    y+=dy; //il personaggio si muove di dy senza
}

void Camera::setCoordinates(float x, float y) {
    if(x >= SCREEN_WIDTH/2) {  //Voglio la camera segua il personaggio solo quando va oltre il punto centrale
        this->x = x;
        healthBar->setPosition(x - width / 2 + 160, this->y - heigth / 2 + 100);
    }
    if(y <= SCREEN_HEIGTH/2) {
        this->y = y;
        healthBar->setPosition(this->x - width / 2 + 160, y - heigth / 2 + 100);
    }
}

Camera::~Camera() {
    delete healthBar;
}

void Camera::updateHealthBar(int hp, int maxHealth) {
    healthBar->update(hp, maxHealth);
}

void Camera::drawHealthBar(sf::RenderWindow &window) const {
    healthBar->draw(window);
}

HealthBar *Camera::getHealthBar() const {
    return healthBar;
}

void Camera::drawGameOver(sf::RenderWindow &window) {
    window.draw(gameoverSpr);
}


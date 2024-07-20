//
// Created by stefano on 7/17/24.
//

#include "Slime.h"
#include"constants.h"
#include"frameTime.h"
#include <iostream>
Slime::Slime(float x, float y, float speed, int hp, EnemyContainer* container): Enemy(x, y, speed, hp, container) {
    runTexture.loadFromFile("../assets/enemyrun.png");
    hitTexture.loadFromFile("../assets/enemyhit.png");
    sprite.setOrigin(22, 15);
    sprite.setScale(3, 3);
    //Correzione per l'origine spostata al centro
    this->x += 22*3;
    this->y += 15*3+7; //Per farlo stare giusto giusto sulla piattaforma
    sprite.setPosition(this->x,this->y);
    rectangle = new Rectangle (x+7,y+8, 40*3, 30*3);
    hitIndex = 0;
    runIndex = 0;
    direction = -1;
    animationType = SlimeAnimationType::Run;
    collisionDmg = 10;
}


void Slime::draw(sf::RenderWindow &window) {
    setAnimation();
    move(direction);
    window.draw(sprite);
    timeFlow();

    //rectangle->draw(window);
}

void Slime::timeFlow() {
    if(frameTime%5==0 && animationType == SlimeAnimationType::Hit)
        hitIndex++;
    if(frameTime%5==0)
        runIndex++;
    if(hitIndex > 4) {
        hitIndex = 0;
        animationType = SlimeAnimationType::Run; //Dopo che finisce l'animazione che viene colpito voglio si passi di nuovo a quela che cammina
    }
    if(hitIndex >= 1 && hp <= 0){
        container->removeEnemy(this); //Prima di morrie voglio facia l'animazione
    }
    if(runIndex > 9)
        runIndex = 0;
}

void Slime::setAnimation() {
    if(animationType == SlimeAnimationType::Run)
        runAnimation();
    else if(animationType == SlimeAnimationType::Hit)
        hitAnimation();
}

void Slime::hitAnimation() {
    sprite.setTexture(hitTexture);
    sprite.setTextureRect(sf::IntRect (44*hitIndex, 0, 44, 30));
}


void Slime::runAnimation() {
    sprite.setTexture(runTexture);
    sprite.setTextureRect(sf::IntRect (44*runIndex, 0, 44, 30));
}

void Slime::hit(int dmg) {
    hp -= dmg;
    animationType = SlimeAnimationType::Hit;
}


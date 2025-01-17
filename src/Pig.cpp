//
// Created by stefano on 7/19/24.
//

#include "../includes/Pig.h"

//
// Created by stefano on 7/17/24.
//

#include "../includes/Pig.h"
#include"../includes/constants.h"
#include"../includes/frameTime.h"
#include <iostream>

Pig::Pig(float x, float y, float speed, int hp, EnemyContainer* container): Enemy(x, y, speed, hp, container) {
    walkTexture.loadFromFile("../assets/pigwalk.png");
    hitTexture.loadFromFile("../assets/pighit.png");
    runTexture.loadFromFile("../assets/pigrun.png");
    sprite.setOrigin(18, 15);
    sprite.setScale(-3, 3); //Imposto anche la direzine inziale, senò va dalla parte opposta
    //Correzione per l'origine spostata al centro
    this->x += 22*3;
    this->y += 15*3+10; //Per farlo stare giusto giusto sulla piattaforma
    sprite.setPosition(this->x,this->y);
    rectangle = new Rectangle (x+10,y+8, 36*3, 30*3);
    hitIndex = 0;
    runIndex = 0;
    walkIndex = 0;
    direction = 1;
    animationType = PigAnimationType::Walk;
    collisionDmg = 7;
}


void Pig::draw(sf::RenderWindow &window) {
    setAnimation();
    move(direction);
    window.draw(sprite);
    timeFlow();
    //rectangle->draw(window);
}

void Pig::timeFlow() {
    if(frameTime%5==0 && animationType == PigAnimationType::Hit)
        hitIndex++;
    if(frameTime%5==0)
        walkIndex++;
    if(frameTime%2==0)
        runIndex++;
    if(hitIndex > 4) {
        hitIndex = 0;
        animationType = PigAnimationType::Run; //Dopo che finisce l'animazione che viene colpito voglio si passi di nuovo a quela che cammina
        speed = 9.f; //Aumenta la sua velocità!!
    }
    if(hitIndex >= 1 && hp <= 0){
        container->removeEnemy(this); //Prima di morrie voglio facia l'animazione
    }
    if(runIndex > 11)
        runIndex = 0;
    if(walkIndex > 15)
        walkIndex=0;
}

void Pig::setAnimation() {
    if(animationType == PigAnimationType::Walk)
        walkAnimation();
    else if(animationType == PigAnimationType::Hit)
        hitAnimation();
    else if(animationType ==PigAnimationType::Run)
        runAnimation();
}

void Pig::hitAnimation() {
    sprite.setTexture(hitTexture);
    sprite.setTextureRect(sf::IntRect (36*hitIndex, 0, 36, 30));
}


void Pig::walkAnimation() {
    sprite.setTexture(walkTexture);
    sprite.setTextureRect(sf::IntRect (36*runIndex, 0, 36, 30));
}

void Pig::runAnimation() {
    sprite.setTexture(runTexture);
    sprite.setTextureRect(sf::IntRect (36*runIndex, 0, 36, 30));
}


void Pig::hit(int dmg) {
    hp -= dmg;
    animationType = PigAnimationType::Hit;
}



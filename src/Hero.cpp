//
// Created by stefano on 7/13/24.
//

#include<iostream>


#include "../includes/Hero.h"
#include"../includes/constants.h"
#include"../includes/frameTime.h"
#include"../includes/PhysicsWorld.h"
#include"../includes/Camera.h"
#include"../includes/HealthBar.h"

using namespace std;

int sign(float x){
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}

Hero::Hero(float x, float y, float speed, int hp): GameCharacter(x, y, speed, hp) {
    weapon.setType(WeaponType::Hero);
    jumping = false;
    idleTime = 0;
    runTime = 0;
    deltaY = 0;
    collidingX = false;
    shootTime = 0;
    collidingEnemy = false;
    camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGTH, speed);
    idleTexture.loadFromFile("../assets/idle.png");
    runTexture.loadFromFile("../assets/run.png");
    jumpTexture.loadFromFile("../assets/jump.png");
    fallTexture.loadFromFile("../assets/fall.png");
    sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
    sprite.setOrigin(16, 16);
    sprite.setPosition(x, y);
    animationType = AnimationType::Idle;
    directionX = 0;
    rectangle = new Rectangle (x-12*SCALE_FACTORX,y-12*SCALE_FACTORY, 24*SCALE_FACTORX, 28*SCALE_FACTORY);
}

void Hero::setAnimation() {
    if(animationType == AnimationType::Idle){
        idleAnimation();
    }
    else if(animationType == AnimationType::Run) {
        runAnimation();
    }
    else if(animationType == AnimationType::Fall){
        fallAnimation();
    }
    else if(animationType == AnimationType::Jump)
        jumpAnimation();
}

void Hero::timeFlow() {
    if(frameTime%3 ==  0) {
        idleTime++;
        runTime++;
    }
    if(idleTime >= 10)
        idleTime = 0;
    if(runTime >=11)
        runTime=0;
    shootTime++;
    if(collidingEnemy){
        collidingTime++;
    }
    if(collidingTime > 30) { //Se colpisce un nemico si ferma per circ 0.5 secondi
        collidingTime = 0;
        collidingEnemy = false;
    }
}



void Hero::move(int dx) {
    if(!collidingEnemy) {
        rectangle->x = x - 12 * SCALE_FACTORX + (float) dx * speed;
        world->fall();
        world->collisionsHandler();
        if (!collidingX) { //nons i muove anche se ha da poco colliso con un nemico
            if (!jumping)   //Se salta si muove più lentamente orizzontalmente
                x += (float) dx * speed;
            else
                x += (float) dx * (speed / 1.75);
            if (dx == 1) {
                sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
                animationType = AnimationType::Run;
            } else if (dx == -1) {
                sprite.setScale(-SCALE_FACTORX, SCALE_FACTORY);
                animationType = AnimationType::Run;
            } else
                animationType = AnimationType::Idle;
            sprite.setPosition(x, y);
        } else
            rectangle->x = x - 12 * SCALE_FACTORX;
        directionX = sign(dx);
    }
}


void Hero::draw(sf::RenderWindow& window) {
    timeFlow();
    if(y >= SCREEN_HEIGTH)
        hit(99999); //Se hero cade muore
    if(hp <= 0)
        camera->gameOver();
    if(jumping) {
        changeY(-17);  //Lo fa saltare
    }
    if(deltaY>0)  //Se sta andando in alto metto l'animazione jump,sennò quella che cade
        animationType = AnimationType::Fall;
    else if(deltaY < 0)
        animationType = AnimationType::Jump;
    deltaY= 0;
    setAnimation();
    sprite.setPosition(x,y);
    camera->update(window);
    float healthBarX = camera->getHealthBar()->getX();
    float healthBarY = camera->getHealthBar()->getY();
    if(animationType!=AnimationType::Idle){ //Se è fermo voglio poter muove la camera con le frecce
        camera->setCoordinates(x,y);
    }
    window.draw(sprite);
    camera->getHealthBar()->setPosition(healthBarX,healthBarY); //Lo devo fare sennò la barra della vita appare scoordinata
    weapon.draw(window);
    //rectangle->draw(window);
}

void Hero::idleAnimation()  {
    sprite.setTexture(idleTexture);
    sprite.setTextureRect(sf::IntRect (idleTime * 32, 0, 32, 32));
    directionX = 0;
}

void Hero::runAnimation() {
    sprite.setTexture(runTexture);
    sprite.setTextureRect(sf::IntRect (runTime * 32, 0, 32, 32));
}

void Hero::jumpAnimation() {
    sprite.setTexture(jumpTexture);
    sprite.setTextureRect(sf::IntRect (0, 0, 32, 32));
}

void Hero::fallAnimation() {
    sprite.setTexture(fallTexture);
    sprite.setTextureRect(sf::IntRect (0, 0, 32, 32));
}


void Hero::changeY(float dy) {
    rectangle->y+=dy;
    world->collisionsHandler();
    if(!collidingY) {
        deltaY += dy;
        y += dy;
    }
    else {
        jumping = false;
        rectangle->y -= dy;
    }
}

void Hero::jump() {
    if(deltaY == 0 && !collidingEnemy) //Se sta cadendo o saltando non pà (ri)saltare
        jumping = true;

}

void Hero::setCollisionX(bool c) {
    collidingX = c;
}

void Hero::setPhysicsWorld(PhysicsWorld *w) {
    world = w;
}

void Hero::setCollisionY(bool c) {
    collidingY = c;
}

void Hero::stopJumping() {
    jumping = false;
}

float Hero::getDeltaY() const {
    return deltaY;
}

void Hero::shoot() {
    //Il proiettile è sparato nella direzione in cui è orientato hero in un certo istante
    if(shootTime >= 60){  //Per non permettergli di sparare troppi colpi
        weapon.shoot(x, y, sign(sprite.getScale().x));
        shootTime = 0;
    }

}

const Weapon &Hero::getWeapon() const {
    return weapon;
}

Camera *Hero::getCamera() const {
    return camera;
}

Hero::~Hero() {
    delete camera;
}

void Hero::hit(int dmg, bool collided ) {
    hp -= dmg;
    camera->updateHealthBar(hp, maxHealth);
    if(collided) { //Se collide con un nemico voglio stia fermo per un poò
        collidingEnemy = true;
        animationType = AnimationType::Idle;
    }
}

void Hero::drawHealthBar(sf::RenderWindow &window) const {
    camera->drawHealthBar(window);
}

int Hero::getDirectionX() const {
    return directionX;
}

bool Hero::getCollidingEnemy() const {
    return collidingEnemy;
}

AnimationType Hero::getAnimationType() const {
    return animationType;
}













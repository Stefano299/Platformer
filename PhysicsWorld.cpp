//
// Created by stefano on 7/14/24.
//

#include "PhysicsWorld.h"
#include"Hero.h"
#include"frameTime.h"
#include"constants.h"
#include"Rectangle.h"
#include"BlockGrid.h"
#include"Block.h"
#include"Bullet.h"
#include "Slime.h"

#include<iostream>
#include"EnemyContainer.h"

PhysicsWorld::PhysicsWorld() {
    fallingT0 = frameTime;
    hero =nullptr;
    enemyContainer = nullptr;
}

void PhysicsWorld::fall() {  //Prende il tempo frame
    long int tInt = (frameTime-fallingT0); //Il tempo trascordo dall'istante inziale, lo faccio scorrere piuttosto velocemente
    float t = tInt*0.1; //Deve essere piccolo
    hero->changeY(t*GRAVITY);
}

void PhysicsWorld::update() {
    collisionsHandler();
    fall(); //Far cadere il personaggio se non cè una piattaforma sotto
    hitDetection();
    enemyMovement();
}

void PhysicsWorld::addHero(Hero *hero) {
    this->hero = hero;
}


bool PhysicsWorld::isColliding(Rectangle* rec1, Rectangle* rec2) const {
    return(rec1->x+rec1->width >rec2->x &&
           rec2->x+rec2->width > rec1->x &&
           rec1->y < rec2->y +rec2->height &&
           rec1->y+rec1->height > rec2->y);
}


void PhysicsWorld::addGrid(BlockGrid *grid) {
    this->grid = grid;
}

void PhysicsWorld::collisionsHandler() {
    bool collidedX = false;
    bool collidedY = false;
    Rectangle* heroRec = hero->getRectangle();
    for(const auto& it: grid->getBlocks()) {
        Rectangle* blockRec = it.getRectangle();
        if (isColliding(heroRec, blockRec)) {
            //Per controllare quando la collisione avviene per il movimento orizzontale di hero contro qualcosa
            if(abs(hero->getY()-HERO_HEIGTH/2-it.getY())< HERO_HEIGTH){  //Se sbatte la  testa sotto una pittaforma smette di saltare
                collidedX = true;
                hero->setCollisionX(true);
                if(abs(hero->getX()-it.getX()) < HERO_WIDTH*(3/2) && heroRec->y > blockRec->y+BLOCK_HEIGTH/2 && hero->getDeltaY()>0) { // CONTROLLA SIA SALENDO!
                    hero->stopJumping();
                    fallingT0 = frameTime-2;
                }
            }
            else{
                collidedY = true;
                hero->setCollisionY(true);
                fallingT0 = frameTime; //Prendo l'istante iniziale in cui cade
            }

        }
    }
    for(const auto& itBlock: grid->getBlocks()){  //Per far scoparire i bullet se colpiscono un blocco
        for(auto itBullet: hero->getWeapon().getBullets()){
            if(isColliding(itBullet->getRectangle(), itBlock.getRectangle())){
                const_cast<Weapon&>(hero->getWeapon()).deleteBullet(itBullet);
            }
        }
    }
    if(!collidedX)
        hero->setCollisionX(false); //Sennè se colldie con un solo blocco non collide affatto
    if(!collidedY) {
        hero->setCollisionY(false);
    }
}

void PhysicsWorld::hitDetection() {  //per individuare quando i nemici sono colpiti
    for(auto itEnemy: enemyContainer->getEnemies()) {
        for (auto itBullet: hero->getWeapon().getBullets()) {
            if (isColliding(itBullet->getRectangle(), itEnemy->getRectangle())) {
                itEnemy->hit(hero->getWeapon().getDamage());
                const_cast<Weapon &>(hero->getWeapon()).deleteBullet(itBullet); //Colpito il nemico il proiettile scompare
            }
        }
    }
}


void PhysicsWorld::enemyMovement() {  //far andare i nemici avanti e indietro su una piattaforma
    for(auto itEnemy: enemyContainer->getEnemies()){
        for(const auto& it: grid->getBlocks()) {
            if(abs(it.getY() - itEnemy->getRectangle()->y) <= BLOCK_HEIGTH ) { //Controllo i blocchi sotto lo slime
                if (itEnemy->getRectangle()->x <= it.getX() && !grid->isBlockPresent(it.getX() - 5, it.getY()) ||
                    itEnemy->getRectangle()->x + (itEnemy->getRectangle()->width - BLOCK_WIDTH) >= it.getX() &&
                    !grid->isBlockPresent(it.getX() + BLOCK_WIDTH + 5, it.getY())) {
                    itEnemy->changeDirection();
                    std::cout << "changing" << std::endl;
                }
            }
        }
    }
}

void PhysicsWorld::addEnemyContainer(EnemyContainer *container) {
    enemyContainer = container;
}



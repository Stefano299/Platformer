//
// Created by stefano on 7/14/24.
//

#include<iostream>

#include "PhysicsWorld.h"
#include"Hero.h"
#include"frameTime.h"
#include"constants.h"
#include"Rectangle.h"
#include"BlockGrid.h"
#include"Block.h"
#include"Bullet.h"
#include"Plant.h"
#include"EnemyContainer.h"
#include"Camera.h"
#include"HealthBar.h"
#include<typeinfo>

using namespace std;

PhysicsWorld::PhysicsWorld() {
    fallingT0 = frameTime;
    hero =nullptr;
    enemyContainer = nullptr;
    heroCollidingBlock = false;
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
    enemiesCollisions();
    enemyMovement();
    plantShoot();
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
    static bool previousCollision = false; //questo metodo viene chiamato due volte e sennò farebbe 01010101010..., quando collide
    bool collidedX = false;
    bool collidedY = false;
    Rectangle* heroRec = hero->getRectangle();
    if(!previousCollision)
        heroCollidingBlock = true;
    else
        heroCollidingBlock = false;
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
    if(collidedX ||  collidedY){
        previousCollision = true;
        heroCollidingBlock = true;
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
            if(isColliding(itEnemy->getRectangle(), it.getRectangle())) { //Controllo i blocchi sotto lo slime
                if (itEnemy->getRectangle()->x <= it.getX() && !grid->isBlockPresent(it.getX() - 5, it.getY()) || //Controlla non ci sia un blocco a sinistra
                    itEnemy->getRectangle()->x + (itEnemy->getRectangle()->width - BLOCK_WIDTH) >= it.getX() &&
                    !grid->isBlockPresent(it.getX() + BLOCK_WIDTH + 5, it.getY())) { //COntrola non ci sia un blocco a destra
                    itEnemy->changeDirection();
                    std::cout << "changing" << std::endl;
                }
            }
        }
    }//abs(it.getY() - itEnemy->getRectangle()->y) <= BLOCK_HEIGTH
}

void PhysicsWorld::addEnemyContainer(EnemyContainer *container) {
    enemyContainer = container;
}

void PhysicsWorld::plantShoot() {
    for(auto itEnemy:  enemyContainer->getEnemies()){
        Plant* plant = dynamic_cast<Plant*>(itEnemy);
        if(plant!= nullptr){//Volgio considerare solo le piante
            float dist = itEnemy->getRectangle()->y-hero->getRectangle()->y;
            if(dist <= hero->getRectangle()->height-20 && dist > 0) { //Mi interessa quando l'eroe è all'altezza della pianta
                plant->changeShootDir(hero->getX()-plant->getX()); //Cambio la direzione della pianta (in base al fatto se hero si trova  a destra e sinistra)
                plant->shoot(); //La pianta spara sull'hero
            }
            for(auto itPlantBullet: plant->getWeapon().getBullets()){
                for(const auto& itBlock: grid->getBlocks()){
                    if(isColliding(itPlantBullet->getRectangle(), itBlock.getRectangle())){
                        const_cast<Weapon&>(plant->getWeapon()).deleteBullet(itPlantBullet); //Voglio scompaglia il proiettile dell pianta se colpisc eun blocco
                    }
                }
                if (isColliding(itPlantBullet->getRectangle(), hero->getRectangle())) {
                    hero->hit(plant->getWeapon().getDamage());
                    const_cast<Weapon &>(plant->getWeapon()).deleteBullet(itPlantBullet); //Colpito il hero il proiettile scompare
                }
            }
        }
    }
}

void PhysicsWorld::enemiesCollisions() {
    for(auto itEnemy: enemyContainer->getEnemies()){
        if(isColliding(itEnemy->getRectangle(), hero->getRectangle())){
            if(heroCollidingBlock) {
                hero->setCollisionX(true); //Hero non sipuò muovere in origgontale in caso li tocchi
                if(typeid(*itEnemy) != typeid(Plant)){
                    itEnemy->changeDirection(); //Il nemico in caso tocchi hero cambia direzione
                    hero->hit(itEnemy->getCollisionDmg(), true);
                }
            }
            else{ //Se hero collide cone enemy da sopra...
                if(itEnemy->getHp() > 0) { //Sennò lo fa più volte
                    itEnemy->hit(9999999); //Muore insomma.
                }
            }
        }
    }
}



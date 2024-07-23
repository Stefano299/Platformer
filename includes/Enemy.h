//
// Created by stefano on 7/18/24.
//

#ifndef PLATFORMER_ENEMY_H
#define PLATFORMER_ENEMY_H

#include"GameCharacter.h"
#include"EnemyContainer.h"

class Enemy: public GameCharacter {
protected:
    int direction;
    EnemyContainer* container; //Cosicche i nemici possano eliminarsi da soli quando finiscono la vita
    int collisionDmg;
public:
    Enemy(float x, float y, float speed, int hp, EnemyContainer* container);
    void move(int dx) override;
    void hit(int dmg) override; //I nemici devono eliminarsi quando colpiti
    int getDirection() const;
    int getCollisionDmg();
    virtual void changeDirection();
};


#endif //PLATFORMER_ENEMY_H

//
// Created by stefano on 7/18/24.
//

#ifndef PLATFORMER_ENEMY_H
#define PLATFORMER_ENEMY_H

#include"GameCharacter.h"

class Enemy: public GameCharacter {
protected:
    int direction;
public:
    Enemy(float x, float y, float speed, int hp): GameCharacter(x,y,speed,hp){}
    void move(int dx) override;
    int getDirection() const;
    virtual void changeDirection();
};


#endif //PLATFORMER_ENEMY_H

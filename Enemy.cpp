//
// Created by stefano on 7/18/24.
//

#include "Enemy.h"

Enemy::Enemy(float x, float y, float speed, int hp, EnemyContainer* container) : GameCharacter(x,y,speed,hp){
    this->container = container;
}

void Enemy::move(int dx) {
    x+=dx*speed;
    rectangle->x+=dx*speed;
    sprite.setPosition(x,y);
}

int Enemy::getDirection() const {
    return direction;
}

void Enemy::changeDirection() {
    direction *= -1;
    sprite.scale(-1.f, 1.f);  //Secambia direzione la texture si capovolge
    move(direction); //Sennò si rimette la collisione (cambia direzione all'infinito)
}

void Enemy::hit(int dmg) {
    hp -= dmg;
    if(hp <= 0)
        container->removeEnemy(this); //Si elimina
}


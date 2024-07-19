//
// Created by stefano on 7/18/24.
//

#include "EnemyContainer.h"
#include"Enemy.h"
#include<algorithm>

void EnemyContainer::addEnemy(Enemy *enemy) {
    enemies.push_back(enemy);
}

void EnemyContainer::removeEnemy(Enemy *enemy) {
    auto it = std::find(enemies.begin(),enemies.end(), enemy);
    if(it != enemies.end())
        enemies.erase(it);
    else
        throw std::invalid_argument("Nemico non esistente");
}

std::vector<Enemy *> &EnemyContainer::getEnemies(){
    return enemies;
}

void EnemyContainer::drawAll(sf::RenderWindow& window) {
    for(auto it: enemies){
        it->draw(window);
    }
}

EnemyContainer::~EnemyContainer() {
    for(auto it:enemies)
        delete it;
    enemies.clear();
}
//
// Created by stefano on 7/18/24.
//

#ifndef PLATFORMER_ENEMYCONTAINER_H
#define PLATFORMER_ENEMYCONTAINER_H

#include<vector>
#include"SFML/Graphics.hpp"

class Enemy;
class EnemyContainer {
private:
    std::vector<Enemy*> enemies;
public:
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);
    std::vector<Enemy*>& getEnemies();
    void drawAll(sf::RenderWindow& window);
    ~EnemyContainer();
};


#endif //PLATFORMER_ENEMYCONTAINER_H

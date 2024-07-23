//
// Created by stefano on 7/18/24.
//

#ifndef PLATFORMER_PLANT_H
#define PLATFORMER_PLANT_H

#include<SFML/Graphics.hpp>

#include"Enemy.h"
#include"Weapon.h"

enum class PlantAnimationType{
    Idle,
    Shoot,
    Hit
};

class Plant: public Enemy {
private:
    void hitAnimation();
    void idleAnimation();
    void shootAnimation();
    void timeFlow();
    void setAnimation();
    sf::Texture hitTexture;
    sf::Texture idleTexture;
    sf::Texture shootTexture;
    PlantAnimationType animationType;
    int shootDirection;
    int idleIndex;
    int shootIndex;
    int hitIndex;
    Weapon weapon;
    int shootTime;
public:
    Plant(float x, float y, float speed, int hp, EnemyContainer* enemyContainer);
    void draw(sf::RenderWindow& window) override;
    void changeShootDir(float dir);
    void shoot();
    const Weapon& getWeapon() const;
    void hit(int dmg) override;
};


#endif //PLATFORMER_PLANT_H

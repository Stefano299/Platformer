//
// Created by stefano on 7/18/24.
//

#include "../includes/PlantBullet.h"
#include "../includes/Rectangle.h"

PlantBullet::PlantBullet(float x, float y, float s, int d) : Bullet(x, y, s, d) {
    texture.loadFromFile("../assets/plantbullet.png");
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    sprite.setScale(3,3);
    rectangle = new Rectangle(x+6,y+6,12*3, 12*3); //Il proiettile è 16x16
}

void PlantBullet::draw(sf::RenderWindow &window) {
    move();
    window.draw(sprite);
    //rectangle->draw(window);
}




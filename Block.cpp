//
// Created by stefano on 7/14/24.
//

#include "Block.h"
#include"constants.h"

Block::Block(float x, float y, Type type) {
    this->x = x;
    this->y = y;
    this->type = type;
    if(type== Type::green)
        texture.loadFromFile("../assets/green.png");
    else if(type == Type::orange)
        texture.loadFromFile("../assets/orange.png");
    else
        texture.loadFromFile("../assets/purple.png");
    sprite.setTexture(texture);
    sprite.setScale(SCALE_FACTORX, SCALE_FACTORY);
    sprite.setPosition(x, y);
}

void Block::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

float Block::getX() const {
    return x;
}

float Block::getY() const {
    return y;
}

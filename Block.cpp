#include "Block.h"
#include "constants.h"
#include <iostream>

// Dichiarazione delle texture come variabili statiche
sf::Texture green;
sf::Texture orange;
sf::Texture purple;
std::map<Type, sf::Texture> Block::textures;

Block::Block(float x, float y, Type type) : x(x), y(y), type(type) {
    auto it = textures.find(type);
    if (it != textures.end()) {
        sprite.setTexture(it->second);
    }
    sprite.setScale(SCALE_FACTORX - 3, SCALE_FACTORY - 3);
    sprite.setPosition(x, y);
}

void Block::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}

float Block::getX() const {
    return x;
}

float Block::getY() const {
    return y;
}

bool Block::operator==(const Block &right) const {
    return (x == right.x && y == right.y);
}

void Block::loadTextures() {
    if (!green.loadFromFile("../assets/green.png")) {
        std::cerr << "Errore nel caricamento della texture green" << std::endl;
    }
    if (!orange.loadFromFile("../assets/orange.png")) {
        std::cerr << "Errore nel caricamento della texture orange" << std::endl;
    }
    if (!purple.loadFromFile("../assets/purple.png")) {
        std::cerr << "Errore nel caricamento della texture purple" << std::endl;
    }
    textures = {{Type::green, green}, {Type::orange, orange}, {Type::purple, purple}};
}

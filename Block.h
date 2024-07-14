//
// Created by stefano on 7/14/24.
//

#ifndef PLATFORMER_BLOCK_H
#define PLATFORMER_BLOCK_H

#include<SFML/Graphics.hpp>

enum class Type{
    green,
    orange,
    purple
};
class Block {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float x;
    float y;
    Type type;
public:
    Block(float x, float y, Type type);
    void draw(sf::RenderWindow& window);
    float getX() const;
    float getY() const;
};


#endif //PLATFORMER_BLOCK_H

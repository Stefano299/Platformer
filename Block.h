//
// Created by stefano on 7/14/24.
//

#ifndef PLATFORMER_BLOCK_H
#define PLATFORMER_BLOCK_H

#include<SFML/Graphics.hpp>
#include<map>

enum class Type{
    green,
    orange,
    purple
};
class Block {
private:
    static std::map<Type, sf::Texture> textures;
    sf::Sprite sprite;
    float x;
    float y;
    Type type;
public:
    Block(float x, float y, Type type = Type::green);
    static void loadTextures();
    void draw(sf::RenderWindow& window) const;
    float getX() const;
    float getY() const;
    bool operator==(const Block& right) const;
};


#endif //PLATFORMER_BLOCK_H

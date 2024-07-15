//
// Created by stefano on 7/14/24.
//

#ifndef PLATFORMER_BLOCKGRID_H
#define PLATFORMER_BLOCKGRID_H

#include<vector>
#include<SFML/Graphics.hpp>
class Block;
class BlockGrid {
private:
    std::vector<Block> blocks;
    int width;
    int height;
public:
    BlockGrid(int width, int height);
    void addBlock(const Block& block);
    void removeBlock(float x, float y);
    void draw(sf::RenderWindow& window) const;
};


#endif //PLATFORMER_BLOCKGRID_H

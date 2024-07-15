//
// Created by stefano on 7/14/24.
//

#include<algorithm>
#include "BlockGrid.h"
#include"Block.h"


BlockGrid::BlockGrid(int width, int height) {
    this->width = width;
    this->height = height;
}

void BlockGrid::addBlock(const Block &block) {
    blocks.push_back(block);
}

/*void BlockGrid::removeBlock(float x, float y) {
    auto it = std::find(blocks.begin(), blocks.end(), Block(x,y));
    if(it != blocks.end())
        blocks.erase(it);
    else
        throw std::invalid_argument("Coordinate per la rimozione del blocco non valide");
}*/

void BlockGrid::draw(sf::RenderWindow &window) const{
    for(const auto& it: blocks)
        it.draw(window);
}

const std::vector<Block> &BlockGrid::getBlocks() const {
    return blocks;
}


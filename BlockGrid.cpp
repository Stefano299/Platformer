//
// Created by stefano on 7/14/24.
//

#include<algorithm>
#include "BlockGrid.h"
#include"Block.h"
#include"constants.h"

BlockGrid::BlockGrid(int width, int height) {
    this->width = width;
    this->height = height;
}

void BlockGrid::addBlock(const Block &block) {
    blocks.push_back(block);
    blocksXY.push_back(sf::Vector2f (block.getX(), block.getY()));
}

void BlockGrid::removeBlock(float x, float y) {
    auto it = std::find(blocks.begin(), blocks.end(), Block(x,y));
    if(it != blocks.end())
        blocks.erase(it);
    else
        throw std::invalid_argument("Coordinate per la rimozione del blocco non valide");
}

void BlockGrid::draw(sf::RenderWindow &window) const{
    for(const auto& it: blocks)
        it.draw(window);
}

const std::vector<Block> &BlockGrid::getBlocks() const {
    return blocks;
}

bool BlockGrid::isBlockPresent(float x, float y) {
    float gridX = ((int)x/(int)BLOCK_WIDTH)*BLOCK_WIDTH;
    float gridY = ((int)y/(int)BLOCK_HEIGTH)*BLOCK_HEIGTH;
    auto it = std::find(blocksXY.begin(), blocksXY.end(), sf::Vector2f (gridX, gridY));
    if(it != blocksXY.end())
        return true;
    else
        return false;
}


#pragma once
#include "grid.hpp"
#include "Block.hpp"
#include "blocks.cpp"

#include <iostream>

class game
{
public:
    game();
    Block getRandomBlock();
    std::vector<Block> getAllBlocks();
    void draw();
    void handleInput();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveAllDown();
    void updatePontuation();
    void resetGame();
    Grid grid;

private:
    bool isBlockOutside();
    void rotateBlock();
    void unableBlock();
    bool blockFits(Block block);

    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    bool IsGameOver;

};
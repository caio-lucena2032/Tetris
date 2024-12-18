#pragma once
#include "grid.hpp"
#include "Block.hpp"
#include "blocks.cpp"

#include <iostream>
#include <time.h>

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
    void shouldIncreaseLevel();
    
    Grid grid;
    int playerPontuation;
    int level;
    double gameSpeed;
    bool IsGameOver;

private:
    bool isBlockOutside();
    void rotateBlock();
    void unableBlock();
    bool blockFits(Block block);

    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
};
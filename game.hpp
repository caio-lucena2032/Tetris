#pragma once
#include "grid.hpp"
#include "Block.hpp"
#include "blocks.cpp"

#include <iostream>
#include <time.h>

class game
{
public:
    
    /*
        Constructor
    */
    game();

    /*
        Draws the grid, current and next block
    */
    void draw();
    
    /*
        Functions to handle the current block moviment and rotation
    */

    void handleInput();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveAllDown();
    void rotateBlock();
    void selectHoldBlock();

    /*
        Functions to update the score and level
    */
    void updateScore();
    void shouldIncreaseLevel();

    /*
        Resets the variables, blocks, grid and score
    */
    void resetGame();
    
    double gameSpeed;
    int playerScore;
    int level;
    bool IsGameOver;
    bool shouldHoldBlock;
    bool holdBlockExists;

private:

    /*
        Gets all blocks and select one randomly until there's none in the array
    */

    Block getRandomBlock();
    std::vector<Block> getAllBlocks();

    /*
        Functions to handle the possible blocks and grid contact
    */
    
    void unableBlock();
    bool blockFits(Block block);
    bool isBlockOutside();

    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Block holdBlock;
    Block auxBlock;
};
#include "game.hpp"
#include <random>

game::game()
{
    this->grid = Grid();

    this->blocks = getAllBlocks();
    this->currentBlock = getRandomBlock();
    this->nextBlock = getRandomBlock();
    this->IsGameOver = false;
    this->playerPontuation = 0;
    this->level = 1;
    this->gameSpeed = 0.5;
}

Block game::getRandomBlock()
{
    if (this->blocks.empty())
    {
        this->blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> game::getAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void game::draw()
{
    grid.draw();
    currentBlock.draw(11, 11);

    switch (this->nextBlock.id)
    {
    case 3:
        this->nextBlock.draw(255, 315);
        break;
    
    case 4:
        this->nextBlock.draw(255, 290);
        break;

    default:
        this->nextBlock.draw(270, 290);
        break;
    }
}

void game::handleInput()
{
    int keyPressed = GetKeyPressed();

    if (this->IsGameOver && keyPressed == KEY_ENTER)
    {
        this->IsGameOver = false;
        this->resetGame();
    }

    switch(keyPressed)
    {
        case KEY_LEFT:
            this->moveLeft();
            break;

        case KEY_RIGHT:
            this->moveRight();
            break;

        case KEY_DOWN:
            this->moveDown();
            break;

        case KEY_UP:
            this->rotateBlock();
            break;

        case KEY_SPACE:
            this->moveAllDown();
            break;
    }
}

void game::moveLeft()
{
    if (!this->IsGameOver)
    {
        this->currentBlock.move(0, -1);
        if (this->isBlockOutside() || this->blockFits(this->currentBlock) == false)
        {
            this->currentBlock.move(0, 1);
        }
    }
}

void game::moveRight()
{
    if (!this->IsGameOver)
    {
        this->currentBlock.move(0, 1);
        if (this->isBlockOutside() || this->blockFits(this->currentBlock) == false)
        {
            this->currentBlock.move(0, -1);
        }
    }
}

void game::moveDown()
{
    if (!this->IsGameOver)
    {
        this->currentBlock.move(1, 0);
        if (this->isBlockOutside() || this->blockFits(this->currentBlock) == false)
        {
            this->currentBlock.move(-1, 0);
            this->unableBlock();
        }
    }
}

void game::moveAllDown()
{
    if (!this->IsGameOver)
    {
        while (!this->isBlockOutside() && this->blockFits(this->currentBlock))
        {
            this->currentBlock.move(1, 0);
        }

        this->currentBlock.move(-1, 0);
        this->unableBlock();
    }
}

void game::rotateBlock()
{
    if (!this->IsGameOver)
    {
        this->currentBlock.rotate();

        if (this->isBlockOutside() || this->blockFits(this->currentBlock) == false)
        {
            this->currentBlock.undoRotatio();
        }
    }
}

bool game::isBlockOutside()
{
    std::vector<position> tiles = currentBlock.getCellPosition();
    for (position item: tiles)
    {
        if (grid.isCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void game::unableBlock()
{
    std::vector<position> tiles = this->currentBlock.getCellPosition();

    for (position item: tiles)
    {
        grid.grid[item.row][item.column] = this->currentBlock.id;
    }

    if (blockFits(nextBlock) == false)
    {
        this->IsGameOver = true;
    }
    
    this->currentBlock = this->nextBlock;
    this->nextBlock = this->getRandomBlock();
    this->playerPontuation +=50;
}

bool game::blockFits(Block block)
{
    std::vector<position> tiles = block.getCellPosition();

    for (position item: tiles)
    {
        if (grid.isCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void game::updatePontuation()
{
    std::vector<int> rowsCompleted = grid.isRowCompleted();
    int differentTypes;

    if (!rowsCompleted.empty())
    {
        for(int item: rowsCompleted)
        {
            differentTypes  = grid.getDifferentTypeInRow(item);
            grid.clearRow(item);
            grid.moveRowsDown(item);
        }

        this->playerPontuation += (300 * (std::size(rowsCompleted)) + 100) * this->level;
        this->playerPontuation += 50 * differentTypes;
    }
}

void game::resetGame()
{
    grid.initialize();
    this->blocks = this->getAllBlocks();
    this->currentBlock = this->getRandomBlock();
    this->nextBlock = this->getRandomBlock();
    this->playerPontuation = 0;
    this->level = 1;
}

void game::shouldIncreaseLevel()
{
    int levelPontuation;

    /*
        Under level 5, the pontuation starts in 10000 points 
        and in each level it's increased 2500 points
    */
    if (this->level < 5)
    {
        levelPontuation = 2000 * this->level + 1000;
    }
    else if (this->level < 10)
    {
        levelPontuation = 4000 * this->level + 9000;
    }
    else if (this->level < 15)
    {
        levelPontuation = 5000 * this->level + 45000;
    }
    else
    {
        levelPontuation = 5000 * this->level + 163000;
    }

    if (this->playerPontuation >= levelPontuation)
    {
        this->level += 1;
        this->gameSpeed -= 0.01;
    }
}

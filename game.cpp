#include "game.hpp"
#include <random>

game::game()
{
    this->grid = Grid();

    this->blocks = getAllBlocks();
    this->currentBlock = getRandomBlock();
    this->nextBlock = getRandomBlock();
    this->IsGameOver = false;
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
    currentBlock.draw();
}

void game::handleInput()
{
    int keyPressed = GetKeyPressed();

    std::cout << "Key pressed ---> " << keyPressed << std::endl;
    std::cout << "is Game over ---> " << this->IsGameOver << std::endl;

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

    if (!rowsCompleted.empty())
    {
        for(int item: rowsCompleted)
        {
            grid.clearRow(item);
            grid.moveRowsDown(item);
        }
    }
}

void game::resetGame()
{
    grid.initialize();
    this->blocks = this->getAllBlocks();
    this->currentBlock = this->getRandomBlock();
    this->nextBlock = this->getRandomBlock();
}
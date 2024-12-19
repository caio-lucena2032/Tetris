#include "game.hpp"
#include <random>

game::game()
{
    this->grid = Grid();

    this->blocks = getAllBlocks();
    this->currentBlock = getRandomBlock();
    this->nextBlock = getRandomBlock();
    this->shouldHoldBlock = true;
    this->holdBlockExists = false;
    this->IsGameOver = false;
    this->playerScore = 0;
    this->level = 1;
    this->gameSpeed = 0.5;

    srand(time(NULL));
}

std::vector<Block> game::getAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
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

void game::draw()
{
    grid.draw();
    currentBlock.draw(11, 11);

    switch (this->nextBlock.id)
    {
    case 3:
        this->nextBlock.draw(255, 225);
        break;
    
    case 4:
        this->nextBlock.draw(255, 210);
        break;

    default:
        this->nextBlock.draw(270, 210);
        break;
    }
    
    if (this->holdBlockExists)
    {
        switch (this->holdBlock.id)
        {
            case 3:
                this->holdBlock.draw(345, 395);
                break;

            case 4:
                this->holdBlock.draw(375, 410);
                break;

            default:
                this->holdBlock.draw(360, 410);
            break;
        }
    }
   
}

void game::handleInput()
{
    int keyPressed = GetKeyPressed();

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

        case KEY_RIGHT_SHIFT:
            this->selectHoldBlock();
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
            this->currentBlock.UndoRotation();
        }
    }
}

void game::selectHoldBlock()
{
    if (this->shouldHoldBlock)
    {
        if (this->holdBlockExists)
        {
            this->auxBlock = this->holdBlock;
            this->holdBlock = this->currentBlock;
            this->currentBlock = this->auxBlock;
        }
        else
        {
            this->holdBlock = this->currentBlock;
            this->currentBlock = this->nextBlock;
            this->nextBlock = getRandomBlock();
            this->holdBlockExists = true;
        }

        this->holdBlock.resetBlock();
        this->currentBlock.resetBlock();

        this->shouldHoldBlock = false;
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
    this->shouldHoldBlock = true;
    this->playerScore +=50;
}

void game::updateScore()
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

        this->playerScore += (300 * (std::size(rowsCompleted)) + 100) * this->level;
        this->playerScore += 50 * differentTypes;
    }

    this->shouldIncreaseLevel();
}


void game::shouldIncreaseLevel()
{
    int levelScore;

    /*
        Under level 5, the score starts in 10000 points 
        and in each level it's increased 2500 points
    */
    if (this->level < 5)
    {
        levelScore = 2000 * this->level + 1000;
    }
    else if (this->level < 10)
    {
        levelScore = 4000 * this->level + 9000;
    }
    else if (this->level < 15)
    {
        levelScore = 5000 * this->level + 45000;
    }
    else
    {
        levelScore = 5000 * this->level + 163000;
    }

    if (this->playerScore >= levelScore)
    {
        this->level += 1;
        this->gameSpeed -= 0.02;
    }
}

void game::resetGame()
{
    grid.initialize();
    this->blocks = this->getAllBlocks();
    this->currentBlock = this->getRandomBlock();
    this->nextBlock = this->getRandomBlock();
    this->playerScore = 0;
    this->level = 1;
    this->IsGameOver = false;
}
#include "Block.hpp"

Block::Block()
{
    this->cellSize = 30;
    this->rotationState = 0;
    this->colors = getCellColors();
    this->rowOffset = 0;
    this->colOffset = 0;
}

void Block::draw(int offsetX, int offsetY)
{
    std::vector<position> blockMatrix = getCellPosition();

    for(position item: blockMatrix)
    {
        DrawRectangle(item.column * cellSize+offsetX, item.row * cellSize+offsetY, cellSize-1, cellSize-1, colors[this->id]);
    }
}

void Block::move(int rows, int columns)
{
    this->rowOffset += rows;
    this->colOffset += columns;
}

void Block::rotate()
{
    this->rotationState++;
    if (this->rotationState == (int)this->cells.size())
    {
        this->rotationState = 0;
    }
}

void Block::UndoRotation()
{
    this->rotationState--;
    if (this->rotationState < 0)
    {
        this->rotationState = (int)this->cells.size() - 1;
    }
}

std::vector<position> Block::getCellPosition()
{
    std::vector<position> blockMatrix = this->cells[this->rotationState];
    std::vector<position> movedblockMatrix;

    for(position item: blockMatrix)
    {
        position newPos = position(item.row + this->rowOffset, item.column + this->colOffset);
        movedblockMatrix.push_back(newPos);
    }
    return movedblockMatrix; 
}

void Block::resetBlock()
{
    this->rotationState = 0;
    this->rowOffset = 0;
    this->colOffset = 0;
}

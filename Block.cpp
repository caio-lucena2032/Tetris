#include "Block.hpp"

Block::Block()
{
    this->cellSize = 30;
    this->rotationState = 0;
    this->colors = getCellColors();
    this->rowOffset = 0;
    this->colOffset = 0;
}

void Block::draw()
{
    std::vector<position> tiles = getCellPosition();

    for(position item: tiles)
    {
        DrawRectangle(item.column * cellSize+11, item.row * cellSize+11, cellSize-1, cellSize-1, colors[this->id]);
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

void Block::undoRotatio()
{
    this->rotationState--;
    if (this->rotationState < 0)
    {
        this->rotationState = (int)this->cells.size() - 1;
    }
}

std::vector<position> Block::getCellPosition()
{
    std::vector<position> tiles = this->cells[this->rotationState];
    std::vector<position> movedTiles;

    for(position item: tiles)
    {
        position newPos = position(item.row + this->rowOffset, item.column + this->colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles; 
}
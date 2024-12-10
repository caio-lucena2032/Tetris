#include "grid.hpp"
#include <iostream>

Grid::Grid()
{
    this->numRows = 20;
    this->numCols = 10;
    this->cellSize = 30;
    this->initialize();
    this->colors = getCellColors();
}

void Grid::initialize()
{
    for (int row = 0; row<this->numRows; row++)
    {
        for (int col = 0; col<this->numCols;col++)
        {
            this->grid[row][col] = 0;
        }
    }
}

void Grid::print()
{
    for (int row = 0; row<this->numCols; row++)
    {
        for (int col = 0; col<this->numCols;col++)
        {
            std::cout << this->grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw()
{
    for (int row = 0; row<this->numRows; row++)
    {
        for (int col = 0; col<this->numCols;col++)
        {
            int cellValue = this->grid[row][col];
            DrawRectangle(col * this->cellSize+1, row * this->cellSize+1, this->cellSize-1, this->cellSize-1, this->colors[cellValue]);
        }
    }
}

bool Grid::isCellOutside(int row, int col)
{
    if (row >= 0 && row < this->numRows && col >= 0 && col < this->numCols)
    {
        return false;
    }
    return true;
}

bool Grid::isCellEmpty(int row, int col)
{
    if (this->grid[row][col] != 0)
    {
        return false;
    }
    return true;
}

std::vector<int> Grid::isRowCompleted()
{
    std::vector<int> vectorOfLinesCompleted;
    for(int row = this->numRows-1; row > 0; row--)
    {
        for (int col=0; col < this->numCols; col++)
        {
            if (grid[row][col] == 0)
            {
                break;
            }
            else if (col == this->numCols - 1)
            {
                vectorOfLinesCompleted.emplace(vectorOfLinesCompleted.begin(), row);
            }
        }
    }
    return vectorOfLinesCompleted;
}

void Grid::clearRow(int rowCompleted)
{
    for (int col=0; col < this->numCols; col++)
    {
        grid[rowCompleted][col] = 0;
    }
}

void Grid::moveRowsDown(int rowCompleted)
{
    for (int row = rowCompleted; row > 0; row--)
    {
        bool isUpperRowEmpty = true;
        for (int col = 0; col < this->numCols; col++)
        {
            grid[row][col] = grid[row-1][col];

            if (grid[row-1][col] != 0)
                isUpperRowEmpty = false;
        }

        if (isUpperRowEmpty)
            return;
    }
}
#pragma once
#include <vector>
#include "raylib.h"
#include "colors.hpp"

class Grid
{
public:
    Grid();
    void initialize();
    void print();
    void draw();
    bool isCellOutside(int row, int col);
    bool isCellEmpty(int row, int col);
    std::vector<int> isRowCompleted();
    void clearRow(int rowCompleted);
    void moveRowsDown(int rowCompleted);
    int getDifferentTypeInRow(int row);

    int grid[20][10];

private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};

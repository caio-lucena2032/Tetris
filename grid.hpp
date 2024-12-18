#pragma once
#include <vector>
#include "raylib.h"
#include "colors.hpp"

class Grid
{
public:
    
    /*
        Constructor
    */
    Grid();

    /*
        Initializes the grid cells in zero
    */
    void initialize();

    /*
        Prints the matrix in terminal
    */
    void print();

    /*
        Draws the grid rectangle with margin and spaces between its cells
    */
    void draw();

    /*
        Verify if the block cell it is outside the grid 
    */
    bool isCellOutside(int row, int col);

    /*
        Verify if the grid cell is empty (value zero)
    */
    bool isCellEmpty(int row, int col);

    /*
        Verify if there is some row completed and returns its amount
    */
    std::vector<int> isRowCompleted();

    /*
        Refine the row completed to zero
    */
    void clearRow(int rowCompleted);

    /*
        Moves the rows above the row completed down
    */
    void moveRowsDown(int rowCompleted);

    /*
        Gets and returns the amount of different types of blocks in the row
    */
    int getDifferentTypeInRow(int row);

    int grid[20][10];

private:
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;
};

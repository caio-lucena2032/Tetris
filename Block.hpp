#pragma once
#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"
#include "raylib.h"

class Block
{
public:
    /*
        Constructor
    */
    Block();

    /*
        Draws the block based in the offset and the tiles
    */
    void draw(int offsetX, int offsetY);

    /*
        Moves the block based on its offset
    */
    void move(int rows, int columns);

   /*
        Rotates the block based on its index rotation state
   */
    void rotate();

    /*
        Undos the rotation backing the index rotation state
    */
    void UndoRotation();

    /*
        Updates the position of each possible block rotation and returns the one current state rotation
    */
    std::vector<position> getCellPosition();

    /*
        Reset the block position
    */
    void resetBlock();


    std::map<int, std::vector<position>> cells;
    int id;

private:
    std::vector<Color> colors;
    int cellSize;
    int rotationState;
    int rowOffset;
    int colOffset;
};
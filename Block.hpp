#pragma once
#include <vector>
#include <map>
#include "position.hpp"
#include "colors.hpp"
#include "raylib.h"

class Block
{
public:
    Block();
    void draw();
    void move(int rows, int columns);
    void rotate();
    void undoRotatio();
    std::vector<position> getCellPosition();
    int id;
    std::map<int, std::vector<position>> cells;

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int colOffset;
};
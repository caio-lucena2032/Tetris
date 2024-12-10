#include "Block.hpp"
#include "position.hpp"

class LBlock: public Block
{
public:
    LBlock()
    {
        this->id = 1;
        this->cells[0] = {position(0, 2), position(1, 0), position(1, 1), position(1, 2)};
        this->cells[1] = {position(0, 1), position(2, 1), position(1, 1), position(2, 2)};
        this->cells[2] = {position(1, 0), position(1, 2), position(1, 1), position(2, 0)};
        this->cells[3] = {position(0, 0), position(0, 1), position(1, 1), position(2, 1)};
        this->move(0, 3);
    }
};

class JBlock: public Block
{
public:
    JBlock()
    {
        this->id = 2;
        this->cells[0] = {position(0, 0), position(1, 0), position(1, 1), position(1, 2)};
        this->cells[1] = {position(0, 1), position(0, 2), position(1, 1), position(2, 1)};
        this->cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 2)};
        this->cells[3] = {position(0, 1), position(1, 1), position(2, 0), position(2, 1)};
        this->move(0, 3);
    }
};

class IBlock: public Block
{
public:
    IBlock()
    {
        this->id = 3;
        this->cells[0] = {position(1, 0), position(1, 1), position(1, 2), position(1, 3)};
        this->cells[1] = {position(0, 2), position(1, 2), position(2, 2), position(3, 2)};
        this->cells[2] = {position(2, 0), position(2, 1), position(2, 2), position(2, 3)};
        this->cells[3] = {position(0, 1), position(1, 1), position(2, 1), position(3, 1)};
        this->move(-1, 3);
    }
};

class OBlock: public Block
{
public:
    OBlock()
    {
        this->id = 4;
        this->cells[0] = {position(0, 0), position(0, 1), position(1, 0), position(1, 1)};
        this->move(0, 4);
    }
};

class SBlock: public Block
{
public:
    SBlock()
    {
        this->id = 5;
        this->cells[0] = {position(0, 1), position(0, 2), position(1, 1), position(1, 0)};
        this->cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 2)};
        this->cells[2] = {position(1, 1), position(1, 2), position(2, 0), position(2, 1)};
        this->cells[3] = {position(0, 0), position(1, 0), position(1, 1), position(2, 1)};
        this->move(0, 3);
    }
};

class TBlock: public Block
{
public:
    TBlock()
    {
        this->id = 6;
        this->cells[0] = {position(0, 1), position(1, 0), position(1, 1), position(1, 2)};
        this->cells[1] = {position(0, 1), position(1, 1), position(1, 2), position(2, 1)};
        this->cells[2] = {position(1, 0), position(1, 1), position(1, 2), position(2, 1)};
        this->cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 1)};
        this->move(0, 3);
    }
};

class ZBlock: public Block
{
public:
    ZBlock()
    {
        this->id = 7;
        this->cells[0] = {position(0, 0), position(0, 1), position(1, 1), position(1, 2)};
        this->cells[1] = {position(0, 2), position(1, 1), position(1, 2), position(2, 1)};
        this->cells[2] = {position(1, 0), position(1, 1), position(2, 1), position(2, 2)};
        this->cells[3] = {position(0, 1), position(1, 0), position(1, 1), position(2, 0)};
        this->move(0, 3);
    }
};
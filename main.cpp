#include "raylib.h"
#include "game.hpp"

#define WIDTH 300
#define HEIGHT 600
#define FPS 60

double lastTimeLoweredBlock = 0;

bool shoulLowerTheBlock(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastTimeLoweredBlock > interval)
    {
        lastTimeLoweredBlock = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "TETRIS");
    SetTargetFPS(FPS);
    
    game tetris = game();

    while(!WindowShouldClose())
    {
        tetris.handleInput();

        if (shoulLowerTheBlock(0.5))
        {
            tetris.moveDown();
        }

        tetris.updatePontuation();
        
        BeginDrawing();
        ClearBackground(SKYBLUE);     
        tetris.draw();
        EndDrawing();
    }

    CloseWindow();
}
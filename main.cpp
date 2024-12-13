#include "raylib.h"
#include "game.hpp"

#define WIDTH 500
#define HEIGHT 620
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

void interfaceDraw(game tetris, Font font)
{
    char scoreText[10];
    sprintf(scoreText, "%d", tetris.playerPontuation);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawRectangleRounded({320, 55, 170, 85}, 0.3, 6, DARKBROWN);
    DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
    DrawTextEx(font, scoreText, {320 + (170-textSize.x)/2, 80}, 38, 2, WHITE);

    DrawTextEx(font, "Next block", {320, 200}, 34, 2, WHITE);
    DrawRectangleRounded({320, 240, 170, 170}, 0.3, 6, DARKBROWN);

    if (tetris.IsGameOver)
    {
        DrawTextEx(font, "Game over", {325, 500}, 34, 2, RED);
        DrawTextEx(font, "Press ENTER to continue", {320, 535}, 12, 2, RED);
    }
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "TETRIS");
    SetTargetFPS(FPS);
    Font font = GetFontDefault();
    game tetris = game();

    while(!WindowShouldClose())
    {
        /*
            Moviment of the player and the blocl
        */
        tetris.handleInput();
        if (shoulLowerTheBlock(tetris.gameSpeed))
        {
            tetris.moveDown();
        }
        
        /*
            Scores of the game
        */
        tetris.updatePontuation();
        tetris.shouldIncreaseLevel();
        
        /*
            Drawing functions
        */
        BeginDrawing();
        ClearBackground(GOLD);
        interfaceDraw(tetris, font);
        tetris.draw();
        EndDrawing();
    }

    CloseWindow();
}
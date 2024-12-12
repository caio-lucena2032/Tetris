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

int main()
{
    InitWindow(WIDTH, HEIGHT, "TETRIS");
    SetTargetFPS(FPS);
    Font font = GetFontDefault();
    
    game tetris = game();

    while(!WindowShouldClose())
    {
        tetris.handleInput();

        std::cout << "Pontuation ---> " << tetris.playerPontuation << std::endl;
        std::cout << "Level ---> " << tetris.level << std::endl;
        std::cout << "Speed ---> " << tetris.gameSpeed << std::endl;

        if (shoulLowerTheBlock(tetris.gameSpeed))
        {
            tetris.moveDown();
        }

        tetris.updatePontuation();
        tetris.shouldIncreaseLevel();
        
        BeginDrawing();
        ClearBackground(SKYBLUE);
        
        char scoreText[10];
        sprintf(scoreText, "%d", tetris.playerPontuation);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        std::cout << font.texture.width << std::endl;

        std::cout << textSize.y << std::endl;

        // textSize is recieving 0


        DrawRectangleRounded({320, 55, 170, 85}, 0.3, 6, DARKBLUE);
        DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
        DrawTextEx(font, scoreText, {320 + (170-textSize.x)/2, 80}, 38, 2, WHITE);

        DrawTextEx(font, "Next block", {320, 200}, 34, 2, WHITE);
        DrawRectangleRounded({320, 240, 170, 170}, 0.3, 6, DARKBLUE);


        tetris.draw();
        EndDrawing();
    }

    CloseWindow();
}
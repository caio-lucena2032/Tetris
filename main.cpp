#include "raylib.h"
#include "game.hpp"
#include "menu.hpp"

#define WIDTH 500
#define HEIGHT 620
#define FPS 60

double lastTimeLoweredBlock = 0;
bool shouldReturnToGame = false;
bool isInMenu = true;

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

void drawGame(game tetris, Font font)
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
    Menu menu = Menu(font);

    while(!WindowShouldClose())
    {
        /*
            Drawing functions
        */
        BeginDrawing();
        ClearBackground(GOLD);

        if ((!tetris.IsGameOver || shouldReturnToGame) && !isInMenu)
        {
            /*
                Scores of the game
            */
            tetris.updatePontuation();
            tetris.shouldIncreaseLevel();


            /*
                Moviment of the player and the block
            */
            tetris.handleInput();
            if (shoulLowerTheBlock(tetris.gameSpeed))
            {
                tetris.moveDown();
            }
            
            drawGame(tetris, font);
            tetris.draw();

            if (shouldReturnToGame)
            {
                tetris.resetGame();
                shouldReturnToGame = false;
                isInMenu = false;
            }
        }
        
        else
        {
            if (GetKeyPressed() == KEY_ENTER || isInMenu)
            {
                isInMenu = true;
                
                /*
                    Defines when should go back to play the game
                */
                shouldReturnToGame = menu.draw();
                isInMenu = !shouldReturnToGame;
            }
            else
            {
                drawGame(tetris, font);
                tetris.draw();
                

            }
        }

        EndDrawing();
    }

    CloseWindow();
}
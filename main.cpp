#include "raylib.h"
#include "game.hpp"
#include "menu.hpp"

#define WIDTH 500
#define HEIGHT 620
#define FPS 60

double lastTimeLoweredBlock = 0;
double initializedTime = 0;
bool shouldReturnToGame = false;
bool isInMenu = true;
bool shouldUpdateBestPlayers = true;

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
    sprintf(scoreText, "%d", tetris.playerScore);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, "Score", {355, 15}, 38, 2, WHITE);
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, DARKBROWN);
    DrawTextEx(font, scoreText, {320 + (170-textSize.x)/2, 67.5}, 38, 2, WHITE);

    DrawTextEx(font, "Next block", {320, 130}, 34, 2, WHITE);
    DrawRectangleRounded({320, 170, 170, 140}, 0.3, 6, DARKBROWN);

    DrawTextEx(font, "Hold block", {320, 330}, 34, 2, WHITE);
    DrawRectangleRounded({320, 370, 170, 140}, 0.3, 6, DARKBROWN);

    if (tetris.IsGameOver)
    {
        DrawTextEx(font, "Game over", {325, 520}, 34, 2, RED);
        DrawTextEx(font, "Press ENTER to continue", {320, 555}, 12, 2, RED);
    }
}

int main()
{
    /*
        Initial configutarions and declarations
    */
    InitWindow(WIDTH, HEIGHT, "TETRIS");
    SetTargetFPS(FPS);
    Font font = GetFontDefault();
    game tetris = game();
    Menu menu = Menu();
    
    /*
        Main loop
    */
    while(!WindowShouldClose())
    {
        /*
            Drawing functions
        */
        BeginDrawing();
        ClearBackground(GOLD);
        
        // Conditional to execute the game
        if ((!tetris.IsGameOver || shouldReturnToGame) && !isInMenu)
        {
            
            /*
                Restart the game and variables to start a new game
            */
            if (shouldReturnToGame)
            {
                tetris.resetGame();
                shouldReturnToGame = false;
                isInMenu = false;
                initializedTime = GetTime();
                shouldUpdateBestPlayers = true;
            }

            // Gets the start game time
            if (!initializedTime)
                initializedTime = GetTime();

            /*
                Moviment of the player and the block
            */
            tetris.handleInput();
            if (shoulLowerTheBlock(tetris.gameSpeed))
            {
                tetris.moveDown();
            }
            
            /*
                Scores of the game
            */
            tetris.updateScore();

            drawGame(tetris, font);
            tetris.draw();
        }

        // conditional to display the menu
        else
        {
            if (GetKeyPressed() == KEY_ENTER || isInMenu)
            {
                isInMenu = true;
                shouldReturnToGame = menu.draw();
                isInMenu = !shouldReturnToGame;
            }

            /*
                The game is over, but draw the game yet waiting for ENTER
            */
            else
            {
                drawGame(tetris, font);
                tetris.draw();
                
                /*
                    Update the best players once after the game end
                */
                if (shouldUpdateBestPlayers)
                {
                    menu.updateBestPlayers(tetris.playerScore, GetTime() - initializedTime);
                    shouldUpdateBestPlayers = false;
                }
                
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
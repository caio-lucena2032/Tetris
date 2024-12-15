#include "menu.hpp"
#include <string.h>

Menu::Menu(Font font)
{
    this->font = font;
    this->players = nullptr;
    this->numOfPlayers = 0;
    this->currentMenu = 0;
}

void Menu::initializeNewPlayer()
{
    this->numOfPlayers++;

    if (numOfPlayers != 1)
    {
        this->players = (player *)realloc(this->players, this->numOfPlayers * sizeof(player));
    }
    else
    {
        this->players = (player *)malloc(this->numOfPlayers * sizeof(player));
    }

    this->players[this->numOfPlayers-1].name = this->getName();
}

char *Menu::getName()
{
    char *name = nullptr;
    
    /*
        Lógica de desenhar botão na tela, imprimir e receber input do texto
    */

    return name;
}

void Menu::draw()
{
    /*
        Fazer a lógica de mudança de Menus
    */

    
    switch(this->currentMenu)
    {
        case menuState::INITIAL_MENU:
            this->drawInitialMenu();
            break;

        case menuState::RULES_MENU:
            break;

        case menuState::PLAYER_MENU:
            break;

        case menuState::BEST_PLAYERS:
            break;
    }
}

void Menu::drawInitialMenu()
{
    char text[25] = "Welcome to Tetris!";
    int textSize = MeasureText(text, 38);
    DrawText(text, 250 - textSize/2, 100, 38, BLACK);
    
    Rectangle playButton = {165, 200, 170, 85};
    strcpy(text, "Play");
    textSize = MeasureText(text, 32);
    DrawRectangleRounded(playButton, 0.3, 6, DARKBROWN);
    DrawText(text, 165 + (170-textSize)/2, 230, 32, WHITE);
    
    Rectangle playersButton = {165, 400, 170, 85};
    strcpy(text, "Top players");
    textSize = MeasureText(text, 27);
    DrawRectangleRounded(playersButton, 0.3, 6, DARKBROWN);
    DrawText(text, 165 + (170-textSize)/2, 430, 27, WHITE);

    Vector2 mousePoint = GetMousePosition();

    if (CheckCollisionPointRec(mousePoint, playButton))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            this->currentMenu = menuState::PLAYER_MENU;
        }
    }

    else if (CheckCollisionPointRec(mousePoint, playersButton))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            this->currentMenu = menuState::BEST_PLAYERS;
        }
    }
}
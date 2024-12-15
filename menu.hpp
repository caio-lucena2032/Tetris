#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "raylib.h"

class Menu
{


public:
    Menu(Font font);
    void initializeNewPlayer();
    void getPlayer();
    void showRules();
    void showBestPlayers();
    void draw();


private:
    struct player
    {
        int bestPontuaion;
        double time;
        char* name;
    };
    player *players;

    int numOfPlayers;
    int currentMenu;
    Font font;

    typedef enum
    {
        INITIAL_MENU = 0,
        RULES_MENU = 1,
        PLAYER_MENU = 2,
        BEST_PLAYERS = 3,
    } menuState;

    char* getName();
    void updateBestPlayers();
    void drawInitialMenu();
};
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "raylib.h"
#include <map>

class Menu
{

public:
    Menu();
    void initializeNewPlayer();
    void showRules();
    void showBestPlayers();
    void updateBestPlayers(int bestPontuation, double time);
    bool draw();


private:
    struct player
    {
        int bestPontuaion;
        double time;
        std::string name;
    };
    player *players;

    typedef enum
    {
        INITIAL_MENU = 0,
        RULES_MENU = 1,
        PLAYER_MENU = 2,
        BEST_PLAYERS = 3,
    } menuState;

    void drawInitialMenu();
    void drawPlayerMenu(); 
    int getPlayerPontuation(std::string name);

    int numOfPlayers;
    int currentMenu;
    int nameLength;
    int numberOfPlayers;
    double lastBarTime;
    bool wasNamePressed;
    bool shouldPlay;
    char name[16];

    std::string fileName;
    std::fstream file;
};
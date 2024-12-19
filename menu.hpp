#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <vector>
#include "raylib.h"
#include <map>

struct player
{
    int bestScore = -1;
    double time = 0;
    std::string name;
};

class Menu
{

public:
    Menu();
    void initializeNewPlayer(std::string name, int score, double time);
    void updateBestPlayers(int bestScore, double time);
    void showBestPlayers();
    bool draw();

private:
    typedef enum
    {
        INITIAL_MENU = 0,
        PLAYER_MENU = 1,
        BEST_PLAYERS = 2,
    } menuState;

    player *players;

    void drawInitialMenu();
    void drawPlayerMenu(); 
    void sortPlayersByScore();
    void getSavedPlayers();
    bool isPlayerIndexInArray(int index, int tam, int arr[]);
    player& getPlayerScore(std::string name);

    double lastBarTime;
    int numOfPlayers;
    int currentMenu;
    int nameLength;
    bool wasNamePressed;
    bool shouldPlay;
    char name[16];

    std::string fileName;
    std::fstream file;
};
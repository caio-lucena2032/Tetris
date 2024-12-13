#include <stdlib.h>
#include <iostream>
#include <time.h>

class menu
{
public:
    menu();
    void initializeNewPlayer();
    void initializeNewTournament();
    void getPlayer();
    void showRules();
    void showBestPlayers();

private:
    typedef struct player
    {
        std::string name;
        int bestPontuaion;
        int day;
        int month;
        int year;
        double time;
        int pontuations[];
    };
    player players[2];

    char* getName();
    void updateBestPlayers();

};
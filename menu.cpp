#include "menu.hpp"

Menu::Menu()
{
    this->players = nullptr;
    this->numOfPlayers = 0;
    this->currentMenu = 0;
    this->wasNamePressed = false;
    
    for (char item: this->name){
        item = '\0';
    }
    this->nameLength = 0;
    this->shouldPlay = false;
    this->lastBarTime = 0;
    this->numberOfPlayers = 0;
    this->fileName = "Best_Players.txt";
}

// void Menu::initializeNewPlayer()
// {
//     this->numOfPlayers++;

//     if (numOfPlayers != 1)
//     {
//         this->players = (player *)realloc(this->players, this->numOfPlayers * sizeof(player));
//     }
//     else
//     {
//         this->players = (player *)malloc(this->numOfPlayers * sizeof(player));
//     }

//     this->players[this->numOfPlayers-1].name = this->getName();
// }

void Menu::updateBestPlayers(int pontuation, double time)
{
    int playerPontuation = this->getPlayerPontuation(this->name);
    
    /*
        In case the player is already in the archive
    */
    if (playerPontuation > -1)
    {
        if (pontuation > playerPontuation)
        {
            this->file.open(this->fileName, std::ios::in);
            std::vector<std::string> lines;
            std::string line;

            while (std::getline(this->file, line))
            {
                if (line == this->name)
                {
                    lines.push_back(line);
                    std::getline(this->file, line);
                    line = std::to_string(pontuation);
                    lines.push_back(line);
                }
                else
                {
                    lines.push_back(line);
                }
            }
            this->file.close();
            this->file.open(this->fileName, std::ios::out);

            while (!lines.empty())
            {
                this->file << lines[0] << std::endl;
                lines.erase(lines.begin());
            }

            this->file.close();   
        }
    
    }
    
    /*
        In case the player is not in the archive
    */
    else
    {
        this->file.open(this->fileName, std::ios::app);
        this->file << this->name << std::endl;
        this->file << pontuation << std::endl;
        this->file << std::endl;
        this->file.close();
    }

    this->file.open(this->fileName, std::ios::in);
    std::map<std::string, std::string> map_players;
    std::string name;
    std::string score;
    while (std::getline(this->file, name))
    {
        if(name != "\n" && !name.empty())
        {
            std::getline(this->file, score);
            map_players[name] = score;
        }
    }
    this->file.close();

    this->file.open(this->fileName, std::ios::out);
    while (!map_players.empty())
    {
        std::string hightestKey;
        int heightestValue = 0;

        for(auto& pair: map_players)
        {
            int playerScore = std::stoi(pair.second);
            if (playerScore > heightestValue)
            {
                hightestKey = pair.first;
                heightestValue = playerScore;
            }
        }
        
        this->file << hightestKey << std::endl;
        this->file << heightestValue << std::endl;
        this->file << std::endl;

        map_players.erase(hightestKey);
    }
    this->file.close();
}


bool Menu::draw()
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
            this->drawPlayerMenu();
            break;

        case menuState::BEST_PLAYERS:
            break;
    }
    
    return this->shouldPlay;
}

void Menu::drawInitialMenu()
{
    this->shouldPlay = false;
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
            strcpy((char *)this->name, "         ");
            this->nameLength = 0;
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

void Menu::drawPlayerMenu()
{
    char text[20] = "Insert your name: ";
    Vector2 mousePoint = GetMousePosition();

    int textSize = MeasureText(text, 34);
    DrawText(text, 250 - textSize/2, 100, 34, BLACK);
    
    strcpy(text, "Min: 4 characteres");
    textSize = MeasureText(text, 18);
    DrawText(text, 250 - textSize/2, 145, 18, BLACK);

    strcpy(text, "Max: 15 characteres");
    textSize = MeasureText(text, 18);
    DrawText(text, 250 - textSize/2, 160, 18, BLACK);
    
    Rectangle nameButton = {115, 200, 270, 85};
    DrawRectangleRounded(nameButton, 0.3, 6, DARKBROWN);

    if (CheckCollisionPointRec(mousePoint, nameButton) || this->wasNamePressed)
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || this->wasNamePressed)
        {            
            this->wasNamePressed = true;
            int keyPressed = GetCharPressed();

            if (keyPressed >= 32 && keyPressed <= 125 && this->nameLength <= 15)
            {
                this->name[this->nameLength] = (char)keyPressed;
                this->nameLength++;
                this->name[this->nameLength] = '\0';
            }

            else if (IsKeyPressed(KEY_BACKSPACE))
            {
                if (this->nameLength >= 0)
                {
                    if (this->nameLength > 0)
                        this->nameLength--;

                    this->name[this->nameLength] = '\0';
                }
            }

            else if (IsKeyPressed(KEY_ENTER) && this->nameLength >= 4)
            {
                this->wasNamePressed = false;
                this->currentMenu = menuState::INITIAL_MENU;
                this->shouldPlay = true;
            }

            strcpy(text, this->name);
            textSize = MeasureText(text, 32);
            DrawText(text, 115 + (270-textSize)/2, 230, 32, WHITE);
        }
        else
        {
            strcpy(text, "        ");
            textSize = MeasureText(text, 32);
            DrawText(text, 115 + (270-textSize)/2, 230, 32, WHITE);
        }
    }
    
    double currentTime = GetTime();
    if (currentTime - this->lastBarTime > 1)
    {
        if (currentTime - this->lastBarTime > 1.75)
            this->lastBarTime = currentTime;


        if (this->nameLength > 0)
            DrawText("|", 115 + textSize + (270-textSize)/2, 230, 32, WHITE);

        else
            DrawText("|", 250, 230, 32, WHITE);
    }
}

int Menu::getPlayerPontuation(std::string name)
{
    this->file.open(this->fileName, std::ios::in);
    std::string line;

    while (std::getline(this->file, line))
    {
        if(line.compare(name) == 0)
        {
            std::getline(file, line);
            this->file.close();
            return std::stoi(line);
        }
    }
    this->file.close();
    return -1;
}

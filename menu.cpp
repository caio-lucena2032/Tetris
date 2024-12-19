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
    this->fileName = "Best_Players.txt";

    if (this->file.is_open())
        this->file.close(); 

    this->getSavedPlayers();
}

void Menu::initializeNewPlayer(std::string name, int score, double time)
{
    /*
        First initialized player
    */
    if (this->players == nullptr)
    {
        this->players = new player[1];
    }

    /*
        Copy the origial players array and adds the new one memory
        and replace the original array
    */
    else
    {
        player* temp = new player[this->numOfPlayers + 1];
        for (int i = 0; i < this->numOfPlayers; i++)
        {
            temp[i] = this->players[i];
        }
        delete[] this->players;
        this->players = temp;
    }
    
    // initialize the variables
    this->players[this->numOfPlayers].bestScore = score;
    this->players[this->numOfPlayers].name = name;
    this->players[this->numOfPlayers].time = time;

    this->numOfPlayers++;
}

void Menu::updateBestPlayers(int playerScore, double time)
{
    /*
        Verify if the player is already saved in the best players file
        Returns the score if exist or -1, in case the player is not saved
    */
    player& playerStrange = this->getPlayerScore(this->name);
    
    /*
        In case the player is already saved in the file
    */
    if (playerStrange.bestScore > -1)
    {
        /*
            Rewrite the file updating the best score, that was the current score recieved
        */
        if (playerScore >= playerStrange.bestScore)
        {
            if(playerScore == playerStrange.bestScore && time < playerStrange.time)
            {
                playerStrange.bestScore = playerScore;
                playerStrange.time = time;
            }
            else
            {
                playerStrange.bestScore = playerScore;
                playerStrange.time = time;
            }
        }
    }
    
    /*
        In case the player is not in the archive, it appends its name and score in it
    */
    else
    {
        this->initializeNewPlayer(this->name, playerScore, time);
    }

    this->sortPlayersByScore();
}

void Menu::showBestPlayers()
{
    char text[30];
    for (int i = 0; i < std::min(10, this->numOfPlayers); i++)
    {
        sprintf(text, "%d. %s ---> %d : %.2f", i+1, this->players[i].name.c_str(), this->players[i].bestScore, this->players[i].time);
        DrawRectangleRounded({10, ((float)i*60)+20, 480, 40}, 0.3, 6, DARKBROWN);
        DrawText(text, 20, ((float)i*60)+30, 20, WHITE);
    }

    if (IsKeyDown(KEY_ENTER))
    {
        this->currentMenu = menuState::INITIAL_MENU;
    }
}

bool Menu::draw()
{
    switch(this->currentMenu)
    {
        case menuState::INITIAL_MENU:
            this->drawInitialMenu();
            break;

        case menuState::PLAYER_MENU:
            this->drawPlayerMenu();
            break;

        case menuState::BEST_PLAYERS:
            this->showBestPlayers();
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

player& Menu::getPlayerScore(std::string name)
{
    for (int i = 0; i < this->numOfPlayers; i++)
    {
        if (this->players[i].name == name)
            return this->players[i];
    }
    
    std::string strange = "Stranger";
    static player invalidPlayer{-1, 0, strange};
    return invalidPlayer;
}

void Menu::sortPlayersByScore()
{
    /*
        Sorts the players by score
    */
    std::sort(this->players, this->players + this->numOfPlayers, [](const player& a, const player& b)
    {
        if (a.bestScore == b.bestScore)
            return a.time < b.time; 

        return a.bestScore > b.bestScore; 
    });
    
    /*
        Writes in the file
    */
    this->file.open(this->fileName, std::ios::out);

    for (int i = 0; i < this->numOfPlayers; i++)
    {
        this->file << this->players[i].name << std::endl;
        this->file << this->players[i].bestScore << std::endl;
        this->file << this->players[i].time << std::endl;
        this->file << std::endl;
    }
    this->file.close();
}

bool Menu::isPlayerIndexInArray(int index, int tam, int arr[])
{
    for (int i = 0; i < tam; i++)
    {
        if (index == arr[i])
            return true;
    }
    return false;
}

void Menu::getSavedPlayers()
{

    this->file.open(this->fileName, std::ios::in);
    std::string line;
    std::string name;
    int score;
    double time;
    while (std::getline(this->file, line))
    {
        if (line != "\n" && !line.empty())
        {
            name = line;

            std::getline(this->file, line);
            score = std::stoi(line);
            std::getline(this->file, line);
            time = std::stod(line);

            this->initializeNewPlayer(name, score, time);   
        }
    }
    this->file.close();
}
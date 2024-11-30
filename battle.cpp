/**
 * @file battle.cpp
 * @author Ryan Matteson and Sutton Jones
 * @brief Holds function definitions.
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "battle.h"
#include <fstream>
/**
 * @brief Prints data to file when called.
 * 
 */
void printDataToFile(ofstream &file, string info)
{
    file << info << endl;
}
/**
 * @brief Displays welcome screen to the game.
 * 
 */
void welcomeScreen(){
    cout << "***** Welcome to Battleship! *****\n\n" << "Rules of the Game:\n" << "1. This is a two player game.\n"
         << "2. Player1 is you and Player2 is the computer.\n" << "3. You must sink all of your enemies ships before they sink yours to win\n"
         << "4. Input coordinates (row,collumn) from 0-9 to indicate a spot on the board to attack or place ships.\n\n" 
         << "Hit enter to start the game!\n";
}
/**
 * @brief Allows user to choose to manually place their ships or have the computer randomly place them.
 * 
 * @return Choice.
 */
int menuOption(){
    int choice;
    cout << "Please select from the following menu:\n" << "1. Enter positions of ships manually.\n"
         << "2. Allow the program to randomly select positions of ships.\n\n" << "Menu choice: ";
    cin >> choice;
    while (choice != 1 && choice != 2){
        cout << "That is not a valid menu option. Input menu option 1 or 2: ";
        cin >> choice;
    }
    return choice;
}
/**
 * @brief Initializes a players board.
 * 
 * @param player1board 
 * @param player2board 
 * @param visibleplayer2board 
 */
void initializeBoards(char player1board[][cols], char player2board[][cols], char visibleplayer2board[][cols], char player1boardpos[][cols], char player2boardpos[][cols]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            player1board[i][j] = '-';
            player2board[i][j] = '-';
            visibleplayer2board[i][j] = '-';
            player1boardpos[i][j] = '-';
            player2boardpos[i][j] = '_';
        }
    }
}
/**
 * @brief Displays player board.
 * 
 * @param board 
 */
void displayboard(char board[][cols], char board2[][cols], char board3[][cols]){
    int ship;
    char letter = 'A';
    cout << "    0 1 2 3 4 5 6 7 8 9\n";
    for (int i = 0; i < rows; i++){
        cout << letter << "   ";
        for (int j = 0; j < cols; j++){
            ship = currentship(board2, i, j);
            if (ship != -1 && sunkShip(board3, ship)){
                cout <<"\033[48;5;"<<21<<";38;5;"<<196<<"m";
                cout << board2[i][j];
            } else {
            if (board[i][j] == 'm' || board[i][j] == '-'){
                cout <<"\033[48;5;"<<21<<";38;5;"<<15<<"m";
            } else {
                cout <<"\033[48;5;"<<238<<";38;5;"<<240<<"m";
            }
            if (board[i][j] == '*'){
                cout <<"\033[48;5;"<<238<<";38;5;"<<196<<"m";
            }
            cout << board[i][j];
            }
            cout <<"\033[48;5;"<<21<<"m";
            if (j == (cols - 1)){
                cout << "\033[0m";
                cout << endl;
            } else {
                bool hship = true;
                for (int w = 0; w < 5; w++){
                    if ((board[i][j] == SHIP_SYMBOLS[w] || board[i][j] == '*') && (board[i][j+1] == SHIP_SYMBOLS[w] || board[i][j+1] == '*')){
                        hship = true;
                        break;
                    } else {
                        hship = false;
                    }
                }
                if (sunkShip(board3, ship)){
                    cout <<"\033[48;5;"<<21<<"m";
                    cout << ' ';
                } else if (hship){
                    cout <<"\033[48;5;"<<238<<"m";
                    cout << ' ';
                } else {
                    cout <<"\033[48;5;"<<21<<"m";
                    cout << ' ';
                }
            }
        }
        cout << "\033[0m";
        letter++;
    }
    cout << endl;
}
/**
 * @brief Detects if ships will intersect eachother.
 * 
 * @param playerBoard Player's board
 * @return true ships will intersect.
 * @return false ships will not intersect.
 */
bool intersectionTest(char playerBoard[][cols], int row, int col, string dir, int shipSize)
{
    if (dir == "right")
    {
        for (int i = col; i - col < shipSize; i++)
        {
            if (playerBoard[row][i] != '-')
            {
                return true;
            }
        
        }
    }
    else
    {
       for (int i = row; i - row < shipSize; i++)
        {
            if (playerBoard[i][col] != '-')
            {
                return true;
            }
        
        } 
    }
    return false;    
}
/**
 * @brief Manually places ships onto board.
 * 
 * @param playerBoard Player 1's Board.
 */
void manuallyPlaceShipsOnBoard(char playerBoard[][cols], char playerBoard2[][cols])
{
    int row = 0, col = 0;
    string dir = "";
    cout << "You have chosen to place the ships manually. Note that the ships can not be placed next to each other.\n";
    for(int ships = 0; ships < 5; ships++)
    {
        displayboard(playerBoard, playerBoard, playerBoard);
        cout << "Now, choose where you want the " << SHIP_NAMES[ships] << " to start and type down or right to make the ship go down or right: ";
        char ship = SHIP_SYMBOLS[ships];
        bool invalid = false;
        do
        {
            
            invalid = false;
            char rowletter;
            row = 0;
            col = 0;
            dir = "";
            cin >> rowletter >> col >> dir;
            if (rowletter >= 97 && rowletter <= 106){ //From the given player letter, if lowercase, it will switch to uppercase.
                rowletter -= 32;
            }
            row = rowletter - 65;
            cin.clear();
            cin.ignore();
            if(playerBoard[row][col] == '-' && playerBoard[row][col + SHIP_SIZES[ships] - 1] == '-' && (playerBoard[row][col-1] == '-' || col == 0) && playerBoard[row][col + SHIP_SIZES[ships]] == '-' && dir == "right" && col <= 10 && (col + SHIP_SIZES[ships] - 1) < 10 && !intersectionTest(playerBoard, row, col, dir, SHIP_SIZES[ships]))
            {//Checks if the ships are on the same row, the space is free, and the ships will not collide then places horizontally. Also they can not be next to each other.
                for (int j = col; j - col < SHIP_SIZES[ships]; j++)
                {
                    playerBoard[row][j] = ship;
                    playerBoard2[row][j] = ship;
                }
            }
            else if (playerBoard[row][col] == '-' && playerBoard[row + SHIP_SIZES[ships] - 1][col] == '-' && (playerBoard[row][col+1] == '-' || col == 9) && (playerBoard[row][col-1] == '-' || col == 0) && dir == "down" && row <= 10 && (row + SHIP_SIZES[ships] - 1) < 10 && !intersectionTest(playerBoard, row, col, dir, SHIP_SIZES[ships]))
            {//Checks if the ships are on the same collumn, the space is free, and the ships will not collide then places vertically. Also they can not be next to each other.
                for (int i = row; i - row < SHIP_SIZES[ships]; i++)
                {
                    playerBoard[i][col] = ship;
                    playerBoard2[i][col] = ship;
                }

            }
            else//If neither of the above it will cout error.
            {
                cout << "Invalid row / collumn try again.: ";
                invalid = true;
            }
        }while (invalid);
        displayboard(playerBoard, playerBoard, playerBoard);
    } 



}
/**
 * @brief Picks a random player (1 or 2).
 * 
 * @return Player number
 */
int randplayer(){
    return rand() % 2 + 1;
}
/**
 * @brief Randomly places ships on board.
 * 
 * @param board Player's board.
 */
void randomPlaceShipBoard(char board[][cols], char board2[][cols]){
    for (int i = 0; i < 5; i++){
        int intersect = 1;
        int direction = rand() % 2 + 1; //Chooses vertical or horizontal for ship. 1 is vertical and 2 is horizontal.
        int srow = rand() % (((rows-1)-SHIP_SIZES[i]) - 0 + 1) + 0, 
            col = rand() % ((cols-1) - 0 + 1) + 0, 
            scol = rand() % (((cols-1)-SHIP_SIZES[i]) - 0 + 1) + 0, 
            row = rand() % ((cols-1) - 0 + 1) + 0;
        if (direction == 1){
            while(intersect == 1){
                for (int l = 0; l < SHIP_SIZES[i]; l++){
                    if (board[srow+l][col] != '-' || board[srow+l][col+1] != '-' || board[srow+l][col-1] != '-'){
                        srow = rand() % (((rows-1)-SHIP_SIZES[i]) - 0 + 1) + 0;
                        col = rand() % ((cols-1) - 0 + 1) + 0;
                        intersect = 1;
                        break;
                    } else {
                        intersect = 0;
                    }
                }
            }
            for (int j = 0; j < SHIP_SIZES[i]; j++){
                board[j+srow][col] = SHIP_SYMBOLS[i];
                board2[j+srow][col] = SHIP_SYMBOLS[i];
            }
        }
        if (direction == 2){
             while(intersect == 1){
                for (int y = 0; y < SHIP_SIZES[i]+1; y++){
                    if (board[row][scol+y] != '-' || (board[row][scol-1] != SHIP_SYMBOLS[i] && board[row][scol-1] != '-')){
                        scol = rand() % (((cols-1)-SHIP_SIZES[i]) - 0 + 1) + 0, 
                        row = rand() % ((cols-1) - 0 + 1) + 0;
                        intersect = 1;
                        break;
                    } else {
                        intersect = 0;
                    }
                }
            }
            for (int x = 0; x < SHIP_SIZES[i]; x++){
                board[row][x+scol] = SHIP_SYMBOLS[i];
                board2[row][x+scol] = SHIP_SYMBOLS[i];
            }
        }
    }
}
/**
 * @brief The function for player 1 to attack. Accepts a row/col and checks if its a hit or miss.
 * 
 * @param board 
 * @param visibleboard 
 * @return string 
 */
string player1Attack(char board[][cols], char visibleboard[][cols],int &hits1,int &miss1, char player2board[][cols]){
    int row;
    int col;
    char rowletter = 0;
    string data;
    cout << "Enter a target: ";
    cin >> rowletter >> col; 
    if (rowletter >= 97 && rowletter <= 106){ //From the given player letter, if lowercase, it will switch to uppercase.
        rowletter -= 32;
    }
    row = rowletter - 65;
    while ((row >= rows || col >= cols || row < 0 || col < 0)||(visibleboard[row][col] == '*' || visibleboard[row][col] == 'm')){
        if (row >= rows || col >= cols || row < 0 || col < 0){
        cout << "That is an invalid row/column, please enter a valid target: ";
        cin >> rowletter >> col;
        } else {
            cout << "You have already guessed that position. Enter a target: ";
            cin >> rowletter >> col;
        }
        if (rowletter >= 97 && rowletter <= 106){
        rowletter -= 32;
        }
        row = rowletter - 65;
    }
    system("clear");
    if (board[row][col] == '-'){
        cout << rowletter << " " << col << " is a miss!\n\n";
        data = "Player1: " + to_string(row) + ", " + to_string(col) + " \"miss\"";
        miss1++;
        visibleboard[row][col] = 'm';
        player2board[row][col] = 'm';
    } else {
        cout << rowletter << " " << col << " is a hit!\n\n";
        data = "Player1: " + to_string(row) + ", " + to_string(col) + " \"hit\"";
        hits1++;
        visibleboard[row][col] = '*';
        player2board[row][col] = '*';
    }
    return data;
}
/**
 * @brief Picks random row/col for player 2 and checks hit or miss on player 1 board.
 * 
 * @param board 
 * @return string 
 */
string player2Attack(char board[][cols],int &hits2, int &miss2){
    int row = rand() % (9 - 0 + 1) + 0;
    int col = rand() % (9 - 0 + 1) + 0;
    char rowletter = 'A' + row;
    string data;
    while (board[row][col] == '*' || board[row][col] == 'm'){
        row = rand() % (9 - 0 + 1) + 0;
        col = rand() % (9 - 0 + 1) + 0;
        rowletter = 'A' + row;
    }
    cout << "Player 2 selects: " << rowletter << " " << col << "\n\n";
    if (board[row][col] == '-'){
        cout << rowletter << "," << col << " is a miss!\n\n";
        data = "Player2: " + to_string(row) + ", " + to_string(col) + " \"miss\"";
        miss2++;
        board[row][col] = 'm';
    } else {
        cout << rowletter << "," << col << " is a hit!\n\n";
        data = "Player2: " + to_string(row) + ", " + to_string(col) + " \"hit\"";
        hits2++;
        board[row][col] = '*';
    }
    cout << "Hit enter to continue!";
    string line = "enter";
    while (line != ""){     //Checks if user hit enter
        cin.ignore();
        getline(cin, line);
    }
    system("clear");
    return data;
}
/**
 * @brief Checks if a certain ship is sunk.
 * 
 * @param board 
 * @param ship 
 * @return true 
 * @return false 
 */
bool sunkShip(char board[][cols], int ship){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (board[i][j] == SHIP_SYMBOLS[ship]){
                return false;
            }
        }
    }
    return true;
}
/**
 * @brief Updates unsunk vectors and takes out any ships that are sunk.
 * 
 * @param board 
 * @param unsunkships 
 * @param player 
 */
void updateSunk(char board[][cols], vector<char> &unsunkships, int player, char player2Board[][cols]){
    int shipnum;
    for (size_t k = 0; k < unsunkships.size(); k++){
        for (int u = 0; u < 5; u++){
            if (SHIP_SYMBOLS[u] == unsunkships[k]){
                shipnum = u;
            }
        }
        if (sunkShip(board, shipnum)){
            char sunkship = unsunkships[k];
            unsunkships[k] = unsunkships[unsunkships.size()-1];
            unsunkships[unsunkships.size()-1] = sunkship;
            unsunkships.pop_back();
            for (int i = 0; i < 5; i++){
                if (SHIP_SYMBOLS[i] == sunkship){
                    if (player == 2){
                        cout << "Player 2 has sunk your " << SHIP_NAMES[i] << "!\n\n";
                    } else {
                        cout << "You have sunk player 2's " << SHIP_NAMES[i] << "!\n\n";
                        }
                        cout << "Hit enter to continue!";
                        string line = "enter";
                        while (line != ""){     //Checks if user hit enter
                            cin.ignore();
                            getline(cin, line);
                        } 
            }
        }
    }
    }
}
/**
 * @brief sends data into file.
 * 
 * @param file file data is written to.
 * @param hits1 player 1 hits.
 * @param miss1 player 1 misses.
 * @param hits2 player 2 hits.
 * @param miss2 player 2 misses
 */
void uploadData(ofstream &file, int hits1, int miss1, int hits2, int miss2){
    if (miss1 == 0)
    {
        miss1 = 1;
    }
    if (miss2 == 0)
    {
        miss2 = 1;
    }
    
    file << "*** Player1 Stats ***" << endl
         << "Number Hits   :  " << hits1 << endl
         << "Number Misses :  " << miss1 << endl
         << "Total Shots   :  " << hits1 + miss1 << endl
         << "Hit/Miss Ratio:  " << hits1 / ((miss1 * 1.0)) * 100.0 << "%" <<endl << endl
         << "*** Player2 Stats ***" << endl
         << "Number Hits   :  " << hits2 << endl
         << "Number Misses :  " << miss2 << endl
         << "Total Shots   :  " << hits2 + miss2 << endl
         << "Hit/Miss Ratio:  " << (hits2 / (miss2 * 1.0)) * 100.0 << '%' << endl;
}
/**
 * @brief Function to determine ship based on coordinates.
 * 
 * @param board 
 * @param row 
 * @param col 
 * @return int 
 */
int currentship(char board[][cols], int row, int col){
    for (int i = 0; i < 5; i++){
        if (board[row][col] == SHIP_SYMBOLS[i]){
            return i;
        }
    }
    return -1;
}
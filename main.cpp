/**
 * @file main.cpp
 * @author Ryan Matteson and Sutton Jones
 * @brief A battleship game between user and computer player.
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <string>
#include "battle.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

int main(){
    vector<char> unsunkships1 = {'c', 'b', 'r', 's', 'd'};
    vector<char> unsunkships2 = {'c', 'b', 'r', 's', 'd'};
    char player1board[rows][cols];
    char player2board[rows][cols];
    char visibleplayer2board[rows][cols]; //A board of just '-' for the user to see. Will display misses and hits.
    char player1boardpos[rows][cols]; //A board to hold the positions of the placed ships on player1board but without setting any * or m. Will use it for the color programming.
    char player2boardpos[rows][cols]; // Same as the player1boardpos but for player 2.
    int hits1 = 0; //Player 1 total hits
    int miss1 = 0; //Player 1 total misses
    int hits2 = 0; //Player 2 total hits
    int miss2 = 0; //Player 2 total misses
    string winner; //Winner
    ofstream battleLog("battleLog.txt");//Checks for battleLog before continuing program.
    if (!battleLog)
    {
        cout << "Error opening file." << endl;
    }
    else
    {
            srand(time(NULL));
            welcomeScreen();

            string line = "enter";
            while (line != ""){     //Checks if user hit enter
                getline(cin, line);
            }
            int option = menuOption();
            initializeBoards(player1board, player2board, visibleplayer2board, player1boardpos, player2boardpos);
            int player = randplayer(); //Variable to hold current player. Is randomly selected at first from function.
            bool isdone = false; //Bool value for game loop.
            if (option == 1){
                manuallyPlaceShipsOnBoard(player1board, player1boardpos);
             } else {
                randomPlaceShipBoard(player1board, player1boardpos);
            }
            randomPlaceShipBoard(player2board, player2boardpos);
            cout << "Player 2 (computer's) board has been generated.\n\n"
                << "Player " << player << " has been randomly selected to go first.\n\n"
                << "Player 1's board: \n\n";
            displayboard(player1board, player1boardpos, player1board);
            cout << "Player 2's board: \n\n";
            displayboard(visibleplayer2board, player2boardpos, player2board);
            while (!isdone) // Game loop till game is done.
            {
                if (player == 1){
                    battleLog << player1Attack(player2board, visibleplayer2board, hits1, miss1, player2board) << endl; // Sends data to batteLog.txt
                    updateSunk(player2board, unsunkships2, player, visibleplayer2board);
                    
                    player = 2;
                } else {
                    battleLog << player2Attack(player1board, hits2, miss2) << endl;// Sends data to batteLog.txt
                    updateSunk(player1board, unsunkships1, player, player2board);
                    player = 1;
                }
                cout << "Player 1's board:\n\n";
                displayboard(player1board, player1boardpos, player1board);
                cout << "\nPlayer 2's board: \n\n";
                displayboard(visibleplayer2board, player2boardpos, player2board);
                for (int win = 0; win < 5; win++){
                    if(sunkShip(player1board, win)){
                        isdone = true;
                    } else if (!(sunkShip(player1board, win))){
                        isdone = false;
                        break;
                    }
                }
                if (isdone == true){
                    cout << "Player 2 wins!\n";
                    battleLog << "Player 2 wins!, Player 1 loses." << endl << endl;
                }
                for (int win2 = 0; win2 < 5; win2++){
                    if(sunkShip(player2board, win2)){
                        isdone = true;
                    } else if (!(sunkShip(player2board, win2))){
                        isdone = false;
                        break;
                    }
                }
                if (isdone)
                {
                    cout << "Player 1 wins!\n";
                    battleLog << "Player 1 wins!, Player 2 loses." << endl << endl;
                }
                
                
            }
    }
    uploadData(battleLog, hits1, miss1, hits2, miss2);
    cout << "Statistics outputted to logfile successfully!" << endl;
    battleLog.close();
    return 0;
}
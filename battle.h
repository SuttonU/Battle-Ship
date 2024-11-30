/**
 * @file battle.h
 * @author Ryan Matteson and Sutton Jones
 * @brief Holds function prototypes
 * @version 0.1
 * @date 2023-11-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef BATTLE_H
#define BATTLE_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;
// Global variables and arrays useful in the program
const int NUM_SHIPS = 5;
const int rows = 10;
const int cols = 10;
// Each of the ships information in 3 arrays (parallel arrays)
const string SHIP_NAMES[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
const char SHIP_SYMBOLS[] = {'c', 'b', 'r', 's', 'd'};
const int SHIP_SIZES[] = {5, 4, 3, 3, 2};
void printDataToFile(ofstream &file, string info);
void welcomeScreen();
int menuOption();
void initializeBoards(char player1board[][cols], char player2board[][cols], char visibleplayer2board[][cols], char player1boardpos[][cols], char player2boardpos[][cols]);
void displayboard(char board[][cols], char board2[][cols], char board3[][cols]);
void manuallyPlaceShipsOnBoard(char playerboard[][cols], char playerBoard2[][cols]);
bool intersectionTest(char playerBoard[][cols], int row, int col, string dir, int shipSize);
int randplayer();
void randomPlaceShipBoard(char board[][cols], char board2[][cols]);
string player1Attack(char board[][cols], char visibleboard[][cols],int &hits1,int &miss1,char player2board[][cols]);
string player2Attack(char board[][cols],int &hits2, int &miss2);
void uploadData(ofstream &file, int hits1, int miss1, int hits2, int miss2);
bool sunkShip(char board[][cols], int ship);
void updateSunk(char board[][cols], vector<char> &unsunkships, int player, char player2Board[][cols]);
int currentship(char board[][cols], int row, int col);
#endif
# PA8_Battleship

### Learner Objectives
At the conclusion of this programming assignment, participants should be able to:
* Initialize, manipulate, and display two-dimensional arrays

### Acknowledgements
Content used in this assignment is based upon information in the following sources:
* This programming assignment is adapted from Dr. Gina Sprint's Computer Science I class at Gonzaga University

## Overview and Requirements

Write a program that simulates the game of [Battleship](http://en.wikipedia.org/wiki/Battleship_(game)). Battleship is a two-player Navy game. The objective of the game is to sink all ships in your enemy's fleet. The Player to sink his/her enemy's fleet first wins.

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://sc01.alicdn.com/kf/HTB1A.E9e5LaK1RjSZFxq6ymPFXa3.jpg" width="350" />

Try playing the online version of the game here https://www.battleshiponline.org/

Both players' fleets consist of 5 ships that are hidden from the enemy. Each ship may be differentiated by its "size" (besides the Cruiser and Submarine) or number of cells it expands on the game board:
1. Carrier has 5 cells
2. Battleship has 4 cells
3. Cruiser has 3 cells
4. Submarine has 3 cells
5. Destroyer has 2 cells.
The program should be built such that the user is Player1 and the computer is Player2. 

For more information about the rules of Battleship visit: [Rules of Battleship](https://www.hasbro.com/common/instruct/Battleship.PDF).

### Game Loops
Almost every game has a **game loop**. A **game loop** runs continuously during gameplay. Each turn of the loop,
* it **processes user input**, 
* **updates the game state**, and
* **renders the game**

It also tracks the passage of time to **control the rate of gameplay**. However, since we will not be doing any game animation, this doesn't really matter in this case.

```cpp
// game setup / initialization

// game Loop
bool isDone = false; // game over???
while (!isDone)
{
    // process input
    // update
    // render
}
```

## Program Details

- [ ] **Two boards** (2-dimensional arrays of chars) exist within the game. 
    * Each 2-dimensional array should be 10 X 10. 
    * One represents Player1's board and one represents Player2's board. 
- [ ] At the beginning of the game, each Players' game board should be initialized to all dashes `-` indicating that no ships have been placed on either board.
- [ ] Before the game starts, Player1 should have the option to either:
    - [ ] manually place each of the 5 ships in his/her fleet or 
    - [ ] to have them randomly placed on the board. 
    - If Player1 decides to place the ships manually, then he/she should be prompted to place the Carrier first, Battleship second, Cruiser third, Submarine fourth, and the Destroyer last. 
    - **Note:** Ships cannot be placed diagonally on the board, they can *only be placed vertically or horizontally* (you don't need to check for this); 
    - [ ] **Validate** if the user tries to place a ship outside the boundaries of the board or on top of a ship that has already been placed.

Each cell on the board that contains part of the ship must be indicated by 
* `c` for Carrier, 
* `b` for Battleship, 
* `r` for Cruiser, 
* `s` for Submarine, or 
* `d` for Destroyer. 

For example, if the Carrier was placed then the board should contain 5 `c` for each cell on the board that has a piece of the Carrier, etc. 

- [ ] Once Player1's ships have been placed, Player2's ships must be randomly placed. Note that the placement of Player2's ships must be unknown to the user. 
- [ ] Thus, Player2's board will only display `-` in each cell after the placement of each ship. 
- [ ] The program should randomly select Player1 or Player2 to go first.

Once it has been decided on which player goes first, the game starts. 
- [ ] Whenever it's Player1's turn, a prompt should be displayed asking for a position to target (specifying where to "shoot") on the enemy's (Player2's) board (2-dimensional array). The position should be specified in terms of a **row and a column** on the board (in that order). The row and column should always be displayed along with the board.
- [ ] If the position specified **Validate** happens to hit a ship, then a `*` should replace the `-` on Player2's board. 
- [ ] (optional) If the hit sinks a ship, replace the `*` on Player2's board with the characters representing the sunk ship (i.e. if the destroyer is sunk, replace the 2 `*` with `d`). 
- [ ] If the position specified misses any one of the ships in the fleet, then an `m` should replace the `-` on Player2's board. 
- [ ] **Validate** that from turn-to-turn **each player should NOT be allowed to enter the same position**. 
- [ ] Also, between turns clear the screen with `system("clear");`

- [ ] In one turn, a player can only take one shot at the enemy's (other player's) fleet. 
- [ ] When Player2 takes a shot at Player1's board, each hit should be specified with a `*` and each miss with a `m` on Player1's board. 
- [ ] The game is over when Player1 or Player2 has sunk all of the ships in the fleet of the enemy.

- [ ] For each move made by Player1 and Player2, the results should be written to a file called **battleship.log**. In this file, you should log the targeted position by each player on each move and whether it was a hit on one of the ships in the fleet. Also, if one of the ships happens to sink, then note this in the log file.
- [ ] At the end of the game, Player1's and Player2's statistics should be written to **battleship.log**. The stats include: 
    * Total number of hits
    * Total number of misses
    * Total number of shots
    * Hits to misses ratio (as a percentage)
    * Won or lost the game

- [ ] Once the game has ended you should write each player's stats to the battleship.log file.

#### Sample batteship.log file
```
Player1: 2,3 "hit"
Player2: 9,9 "miss"
Player1: 2,4 "hit"
Player2: 3,7 "miss"
Player1: 2,5 "hit" Sunk Submarine!
Player2: 1,6 "miss"
.
.
.
.
.
.
Player1 wins, Player2 loses

*** Player1 Stats ***
Number Hits   :  17
Number Misses :  32
Total Shots   :  49
Hit/Miss Ratio:  34.694%

*** Player2 Stats ***
Number Hits   :   9
Number Misses :  39
Total Shots   :  48
Hit/Miss Ratio:  18.750%
```

### Three File Structure
- [ ] Program MUST use three file structure. Create the files **main.cpp**, **battleship.cpp**, and **battleship.h**

### Global Constants to Define
- [ ] Declare the global constants below in **battleship.h**. You **MUST** used these variables and arrays in your program.
```cpp
// Global variables and arrays useful in the program
const int NUM_ROWS = 10;  // number of rows of the battleship game board
const int NUM_COLS = 10;  // number of columns of the battleship game board
const int NUM_SHIPS = 5;  // number of ships in the battelship game

// Each of the ships information in 3 arrays (parallel arrays)
const string SHIP_NAMES[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
const char SHIP_SYMBOLS[] = {'c', 'b', 'r', 's', 'd'};
const int SHIP_SIZES[] = {5, 4, 3, 3, 2};
```

### Functions to Define
The first step is to draw a structure or hierarchy chart to help you understand the decomposition of functions for this program. Remember to start with the overall problem and break it down into inputs, computations, and outputs. One possible functional decomposition includes the following (Note: **you are NOT REQUIRED to apply these functions** and  in your program!):
- [ ] Create a function `welcomeScreen()` that displays an initial program welcome message along with the rules of Battleship.
- [ ] Create a function `initializeBoard()` that sets each cell in a game board to `-`.
- [ ] Create a function `displayBoard()` that displays a board to the screen. Note that Player1's board should be displayed differently than Player2's board (see above and the example output below).
    * Since this function will be use to print both Player 1 and 2's board to the screen. During the game, Player 2's (computer) board game should have the ships invisible to the other player. Thus, the parameter `showShips` will be used to determine whether to print out the ships in the screen or hide them. This will also be useful during debugging, while you haven't completed the program, you can show the ships to the screen for both players, but once you complete writing the program, just set `showShips` to `false` so ships are hidden.
- [ ] Create a function `manuallyPlaceShipsOnBoard()` that allows the user to place each of the 5 types of ships on his/her game board.
- [ ] Create a function `randomlyPlaceShipsOnBoard()` that randomly places the 5 types of ships on a given board.
- [ ] Create a function `selectWhoStartsFirst()` that determines if Player1 or Player2 goes first in the game.
- [ ] Create a function `checkShotIsAvailable()` returns `true` if position entered is still available, otherwise return false. **Note**, each player should NOT be allowed to enter the same position.
- [ ] Create a function `isWinner()` that determines if a winner exists.
- [ ] Create a function `updateBoard()` that updates the board every time a shot is taken. Updates the board position with `'*'` indicates a hit and `'m'` indicates a miss. Function also returns an integer. If the shot is a miss, then function returns `-1`, otherwise if it is a hit, function return `0` for hitting the carrier, `1` for hitting the battleship, `2` for hitting the cruiser, `3` for hitting the submarine, and `4` for hitting the destroyer.
- [ ] Create a function `outputCurrentMove()` that writes the position of the shot taken by the current player to the log file.
    * It also writes whether or not it was a hit, miss, and if the ship was sunk.
- [ ] Create a function `updateShipSize()` updates the ship size if a ship is hit and returns `true` if the ship has sunk and `false` otherwise.
    * **Hint:** Create two arrays in `main()` representing the size of each ship. One array for each player. When a specific ship gets hit, decrement the size of the ship that was hit. If during the current move, the size of a ship becomes zero, then the ship has sunk.
- [ ] Create a function `outputStats()` that writes the statistics collected on each player to the log file.
- [ ] Other functions that you think are necessary!
- [ ] The `main()` function that does the following:
    - [ ] Opens an output file **battleship.log** for writing;
    - [ ] Simulates the game of Battleship
    - [ ] Outputs data to the log file
    - [ ] Outputs stats to the log file
    - [ ] Closes the log file

### Documentation
* You MUST write line comments to explain sections of your code to increase its readability. 
* You MUST also write function header comments to all your functions. Follow the format taught in the lecture and lab. Describe what the function does, description of each parameter if needed and a description of what the function returns if needed.

```cpp
/**
 * @brief DESCRIBE WHAT FUNCTION DOES
 *
 * @param PARAMETER_NAME  DESCRIBE PARAMETER
 * @param PARAMETER_NAME  DESCRIBE PARAMETER
 * @return RETURN_TYPE    DESCRIBE WHAT FUNCTION RETURNS
 */
```

### Sample Run
The following sample session demonstrates how your program should work (user input is shown in bold).
<pre>
***** Welcome to Battleship! *****

Rules of the Game:
1. This is a two player game.
2. Player1 is you and Player2 is the computer.
3. Etc. (You need to list the rest of the rules here.)

Hit enter to start the game!

<Enter>

<clear the screen>

Please select from the following menu:
1. Enter positions of ships manually.
2. Allow the program to randomly select positions of ships.

Menu choice: 1

Please enter start row and column to place the Carrier: <strong>0 2</strong>
Place it in [0] horizontal or [1] vertical: <strong>0</strong>

Please enter start row and column to place the Battleship: <strong>3 4</strong>
Place it in [0] horizontal or [1] vertical: <strong>1</strong>

Etc......

Player2 (Computer's) board has been generated.

Player1 has been randomly selected to go first.

Player1's Board:

    0 1 2 3 4 5 6 7 8 9
0   - - c c c c c - - -
1   d d - - - - - - - -
2   - - - - - - - - - s
3   - - - - b - - - - s
4   - - - - b - - - - s
5   - - - - b - - - - -
6   - - - - b - - - - -
7   - - - r r r - - - -
8   - - - - - - - - - -
9   - - - - - - - - - -

Player2's Board:

   0 1 2 3 4 5 6 7 8 9
0  - - - - - - - - - -
1  - - - - - - - - - -
2  - - - - - - - - - -
3  - - - - - - - - - -
4  - - - - - - - - - -
5  - - - - - - - - - -
6  - - - - - - - - - -
7  - - - - - - - - - -
8  - - - - - - - - - -
9  - - - - - - - - - -

Enter a target: <strong>2 3</strong>

(clear screen)

2,3 is a hit!

Player1's Board:

   0 1 2 3 4 5 6 7 8 9
0  - - c c c c c - - -
1  d d - - - - - - - -
2  - - - - - - - - - s
3  - - - - b - - - - s
4  - - - - b - - - - s
5  - - - - b - - - - -
6  - - - - b - - - - -
7  - - - r r r - - - -
8  - - - - - - - - - -
9  - - - - - - - - - -

Player2's Board:

   0 1 2 3 4 5 6 7 8 9
0  - - - - - - - - - -
1  - - - - - - - - - -
2  - - - * - - - - - -
3  - - - - - - - - - -
4  - - - - - - - - - -
5  - - - - - - - - - -
6  - - - - - - - - - -
7  - - - - - - - - - -
8  - - - - - - - - - -
9  - - - - - - - - - -

Player2 selects: <strong>9 9</strong>

9,9 is a miss!

Hit enter to continue!

Enter

(clear screen)

Player1's Board:

   0 1 2 3 4 5 6 7 8 9
0  - - c c c c c - - -
1  d d - - - - - - - -
2  - - - - - - - - - s
3  - - - - b - - - - s
4  - - - - b - - - - s
5  - - - - b - - - - -
6  - - - - b - - - - -
7  - - - r r r - - - -
8  - - - - - - - - - -
9  - - - - - - - - - m

Player2's Board:

   0 1 2 3 4 5 6 7 8 9
0  - - - - - - - - - -
1  - - - - - - - - - -
2  - - - * - - - - - -
3  - - - - - - - - - -
4  - - - - - - - - - -
5  - - - - - - - - - -
6  - - - - - - - - - -
7  - - - - - - - - - -
8  - - - - - - - - - -
9  - - - - - - - - - -

(etc…)

Player1 Wins!

Statistics outputted to logfile successfully!
</pre>



## Extensions (Not Required)
* In the actual game of Battleship, rows are labeled with letters `'A'-'J'` instead of digits `0-9`. Change your program so rows use `'A'-'J'` 
    * Display your grids with rows `'A'-'J'`
    * Allow the user to enter a row using `'A'-'J'`
    * Show the computer’s shots fired using rows `'A'-'J'`
* Read about `struct` in Gaddis book. Throughout the game, keep track of the statistics in a structure called `Stats`. You will need two variables of type `Stats`, one for Player1 and one for Player2. When the game ends, write the contents of each struct variable to the **battleship.log** file.


## Submitting Assignments
* It is VERY IMPORTANT that besides pushing the code to GitHub that you still submit the GitHub URL of this lab assignment in Canvas. This allows the instructor to be notified of your final submission.

> **_NOTE: By submitting your code to be graded, you are stating that your submission does not violate the Academic Integrity Policy outlined in the syllabus._**

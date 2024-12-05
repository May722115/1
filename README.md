# COMP2113 Project
Chan Chi Ngai 3036224602
Lee Jaimie 3035855179
HU BUYUE 3036253706
Jia Aiwei 3036136386
Su Nan 3036265072

**-- Description --** 

This code mimics the game of Sudoku with 3 different levels (easy, medium, and hard). The levels vary depending on the number of initially given clues. For example, the easy level will have the most initialized clues while the hardest level will have the least initialized clues. Each game shall be recorded under a _record table_ where the scoreboard will be seen according to time of completion and board difficulty. 

**-- Quick Start --**
Use command "make main" to compile. If compilation succeeds, the a file called "main" shoule be present. Then type "./main" to run the game.

**-- Game Play --** 

**It's time to play a game of Sudoku!**
**Objective:**
The goal of Sudoku is to fill a 9x9 grid with numbers so that each row, each column, and each of the nine 3x3 subgrids (also known as regions or boxes) contain all of the digits from 1 to 9.

**Starting Grid:**
A Sudoku puzzle starts with some cells already filled in. These cells cannot be changed.

**Rules:**
Each row, column, and 3x3 subgrid must contain all the numbers from 1 to 9 without repetition.
You need to fill in the empty cells in a way that satisfies the above rule.

**Commands:**
Enter the command "play" to start playing a game.
Enter the command "records" to see the current scoreboard, if any. If there have been no games played, no records will be found. Start a game to start a record!
Enter the command "exit" to exit the programm.

**Filling Cells:**
While playing the game. Enter "add","remove","save" and "quit" to implement the corresponding function.
Add: Type in Row, Column and number to fill a number into a position.
Remove: Type in Row and Column to remove a number from a position.
Save: Save the current game and go back to main menue.
Quit: directly go back to main menue.


**-- Non-standard C++ Libraries --**

#include "generate_hard.h"
#include "generate_function.h"
#include "play_game.h"

**-- Coding Features --**
1. Generation of random events
   Random number generation is used for creating a complete game board randomly each time in function generateboard().
2. Data structures for storing data
   Int array is used to store the gameborad while vector<string> structure is used to store the gameboard with format shown in board.txt. 
3. Dynamic memory management
   
4. File input/output (e.g., for loading/saving data)
   The complete board generate in function generateboard() is outputed as file answer.txt in function storeanswer() for later reference.
5. Program codes in multiple files

   
   

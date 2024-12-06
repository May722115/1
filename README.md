# COMP2113 Project
Chan Chi Ngai 3036224602
Lee Jaimie 3035855179
HU BUYUE 3036253706
Jia Aiwei 3036136386
Su Nan 3036265072

**-- Description --** 

This code mimics the game of Sudoku with 3 different levels (easy, medium, and hard). The levels vary depending on the number of initially given clues. For example, the easy level will have the most initialized clues while the hardest level will have the least initialized clues. Each game shall be recorded under a _record table_ where the scoreboard will be seen according to time of completion and board difficulty. 

**-- Quick Start --**
Use command "make main" to compile. If compilation succeeds, the a file called "main" shoule be created. Then type "./main" to run the game.

**-- Game Play --** 

**It's time to play a game of Sudoku!**
**Objective:**
The goal of Sudoku is to fill a 9x9 grid with numbers so that each row, each column, and each of the nine 3x3 subgrids (also known as regions or boxes) contain all of the digits from 1 to 9.

**Starting Grid:**
A Sudoku puzzle starts with some cells already filled in. These cells cannot be changed.
Choose Level 1 for easy, Level 2 for medium and Level 3 for hard.

**Rules:**
Each row, column, and 3x3 subgrid must contain all the numbers from 1 to 9 without repetition.
You need to fill in the empty cells in a way that satisfies the above rule.

**Commands:**
Enter the command "play" to start playing a game. You can use "new" to start a new game or "load" to load your previous incomplete game.
Enter the command "records" to see the current scoreboard, if any. If there have been no games played, no records will be found. Start a game to start a record!
Enter the command "exit" to exit the programm.

**Filling Cells:**
While playing the game. Enter "add", "remove", "save" and "quit" to implement the corresponding function.
Add: Type in Row, Column and number to fill a number into a position.
Remove: Type in Row and Column to remove a number from a position.
Save: Save the current game and go back to main menu.
Quit: directly go back to main menue.


**-- Non-standard C++ Libraries --**

#include "generate_hard.h" in generate_hard.cpp and main.cpp. 
Generate_hard.h together with generate_hard.cpp are used for forming generate_hard.o.
#include "generate_function.h" in generate_function.cpp and main.cpp. 
Generate_function.h together with generate_function.cpp are used for forming generate_function.o.
#include "play_game.h" in play_game.cpp and main.cpp. Play_game.h together with play_game.cpp are used for forming play_game.o.
Generate_hard.h, generate_function.h, play_game.h and main.cpp are used together to form main.o.

**-- Coding Features --**
1. Generation of random events
   Random number generation is used for creating a complete game board(without removing any hints) randomly each time in function generateboard(). It 
   is also used for randomly choosing a coordinate in the game board when removing the hints to create the problem.
2. Data structures for storing data
   Int array is used to store the gameborad while vector<string> structure is used to store the gameboard with format shown in board.txt. 
3. Dynamic memory management
   Vector structure is used for storing game board with indications on the top and left. Data is stored as string in this vector<string> structure. 
   Data stored are changed as user add or delete their answers.
4. File input/output (e.g., for loading/saving data)
   The complete board generate in function generateboard() is outputed as file answer.txt in function storeanswer() for later reference. During the 
   game, user could choose to save their current game as an external file. When they enter the game again, they can choose to load the previous game 
   from this external file. The game record is also saved as an external file. Programm will read the file every time user wants to see the current 
   record list.
5. Program codes in multiple files
   The functions used to generate gameboard, remove hints, add and delete number, and save the game are written in separate .cpp files. There are 3 
   separated .cpp files: generate_function.cpp, generate_hard.cpp and play_game.cpp. 
   
   

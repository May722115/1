# COMP2113 Project
Chan Chi Ngai 3036224602
Lee Jaimie 3035855179

**-- Description --** 

This code mimics the game of Sudoku with 3 different levels (easy, medium, and hard). The levels vary depending on the number of initially given clues. For example, the easy level will have the most initialized clues while the hardest level will have the least initialized clues. Each game shall be recorded under a _record table_ where the scoreboard will be seen according to time of completion and board difficulty. 

**-- Game Play --** 

**It's time to play a game of Sudoku!**
**Objective:**
The goal of Sudoku is to fill a 9x9 grid with numbers so that each row, each column, and each of the nine 3x3 subgrids (also known as regions or boxes) contain all of the digits from 1 to 9.

**Starting Grid:**
A Sudoku puzzle starts with some cells already filled in. These cells cannot be changed.

**Rules:**
Each row, column, and 3x3 subgrid must contain all the numbers from 1 to 9 without repetition.
You need to fill in the empty cells in a way that satisfies the above rule.

**Filling Cells:**


**Commands:**
Enter the command "records" to see the current scoreboard, if any. If there have been no games played, no records will be found. Start a game to start a record!

**-- Non-standard C++ Libraries --**

#include "generate_hard.h"
#include "generate_function.h"
#include "play_game.h"

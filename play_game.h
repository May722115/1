#ifndef PLAY_GAME_H
#define PLAY_GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Global variables
extern vector<vector<int>> board; 
extern vector<vector<int>> sudoku; 
extern string filename; 
extern string answer_file; 

// Function prototypes
void load_game(); 
void add(int row, int column, int number); 
void remove(int row, int column); 
void save(); 
bool check_completion(); 
void formatting(vector<string>& board, const vector<vector<int>>& sudoku); 

#endif 

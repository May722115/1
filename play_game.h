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
void load_game(int sudoku[][9], vector<string> &board); 
void add(int row, int column, int number, int sudoku[][9], std::vector<std::string> &board); 
void remove(int row, int column,int sudoku[][9], std::vector<std::string> &board); 
void save(int sudoku[][9]); 
bool check_completion(int sudoku[][9]); 


#endif 

#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

extern vector<vector<int>> board; 
extern vector<vector<int>> sudoku; 
extern string filename;
extern string answer_file;

void display_board();
void load_game();
void add(int row, int column, int number);
void remove(int row, int column);
void save();
void check_completion();
void formatting();

#endif

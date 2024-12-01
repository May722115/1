#ifndef GENERATE_FUNCTION_H
#define GENERATE_FUNCTION_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <cmath>
#include <cstring>
#include <ctime>
#include <bitset>

extern int resultNum;
extern int answer[9][9];
extern int tempSudoku[9][9];
extern int copy[9][9];

bool checkvalid(int numberboard[][9], int number, int row, int col);
bool generateboard(int numberboard[][9], int row, int col);
bool hasSingleSolution(int sudoku[][9], int level);
void removeElements(int sudoku[][9], int sudoku_copy[][9], int count, int level);
void solve(int data[][9], int sudoku_copy[][9], int level);
void analyse(int data[][9]);
int check(int data[][9]);
int* findLessCandidatesPos(int data[][9]);
void printByRow(int data[][9], int sudoku_copy[][9]);
void binaryToInt(int data[][9]);

#endif

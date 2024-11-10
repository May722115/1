#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

//check whether generated number is valid (not repeated)
bool checkvalid(int number, int row, int col){
    //check for row
    for (int i = 0; i < 9; i++){
        if (numberboard[row][i] == number){
            return false;
        }
    }

    //check for colunm
    for (int i = 0; i < 9; i++){
        if (numberboard[i][col] == number){
            return false;
        }
    }

    //check for 3x3 matrix
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (numberboard[(row / 3 * 3) + i][(col / 3 * 3) + j] == number){
                return false;
            }
        }
    }
    return true;
}

//Randomly generate a sudoku board filled with numbers
bool generateboard(int numberboard[][9], int row, int col){
    int number;
    if (row == 8 && col == 9){
        return true;
    }
    if (col == 9){
        row += 1;
        col = 0;
    }
    if (numberboard[row][col] != 0){
        return generateboard(numberboard, row, col+1);
    }

    for (int i = 1; i < 10; i++){
        number = rand() % 9 + 1;
        if (checkvalid(number, row, col)){
            numberboard[row][col] = number;
            if (generateboard(numberboard, row, col+1)){
                return true;
            }
            numberboard[row][col] = 0;
        }
    }
    return false;
}

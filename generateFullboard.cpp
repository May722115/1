#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

//Check for validity of value generated at each position
bool checkvalid(int numberboard[][9], int number, int row, int col) {
    //check for columns
    for (int i = 0; i < 9; i++) {
        if (numberboard[row][i] == number) {
            return false;
        }
    }

    //check for rows
    for (int i = 0; i < 9; i++) {
        if (numberboard[i][col] == number) {
            return false;
        }
    }

    //check for 3x3 matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (numberboard[(row / 3 * 3) + i][(col / 3 * 3) + j] == number) {
                return false;
            }
        }
    }
    return true;
}

//generate full number board
bool generateboard(int numberboard[][9], int row, int col) {
    //check whether all rows are filled
    if (row == 8 && col == 9) {
        return true;
    }

    //check whether all colunms in the row are filled
    if (col == 9) {
        row++;
        col = 0;
    }

    //check whether the position is filled
    if (numberboard[row][col] != 0) {
        return generateboard(numberboard, row, col + 1);
    }

    //fill the number in a row
    for (int i = 1; i <= 9; i++) {
        //randomly generateing a number
        int number = rand() % 9 + 1;
        //check if the number if valid and fill it in the position
        if (checkvalid(numberboard, number, row, col)) {
            numberboard[row][col] = number;
            //check whether next valid number exists, repeat previous step if not
            if (generateboard(numberboard, row, col + 1)) {
                return true;
            }
            numberboard[row][col] = 0;
        }
    }
    return false;
}

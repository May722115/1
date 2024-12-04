#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
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

bool generateboard(int numberboard[][9], int row, int col) {
    // Check whether all rows are filled
    if (row == 8 && col == 9) {
        return true;
    }

    // Move to the next row if the current row is filled
    if (col == 9) {
        row++;
        col = 0;
    }

    // Skip already filled positions
    if (numberboard[row][col] != 0) {
        return generateboard(numberboard, row, col + 1);
    }

    // Create and shuffle numbers 1 to 9
    int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_shuffle(numbers, numbers + 9);

    // Try filling the position with shuffled numbers
    for (int i = 0; i < 9; i++) {
        int number = numbers[i]; // Get the next shuffled number
        if (checkvalid(numberboard, number, row, col)) {
            numberboard[row][col] = number;
            if (generateboard(numberboard, row, col + 1)) {
                return true; // If board generation is successful, return true
            }
            // Backtrack if placing the number leads to no solution
            numberboard[row][col] = 0;
        }
    }

    return false; 
}

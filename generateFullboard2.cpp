#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <random> // Required for std::shuffle
using namespace std;

// Check for validity of value generated at each position
bool checkvalid(int numberboard[][9], int number, int row, int col) {
    // Check for columns
    for (int i = 0; i < 9; i++) {
        if (numberboard[row][i] == number) {
            return false;
        }
    }

    // Check for rows
    for (int i = 0; i < 9; i++) {
        if (numberboard[i][col] == number) {
            return false;
        }
    }

    // Check for 3x3 subgrid
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (numberboard[startRow + i][startCol + j] == number) {
                return false;
            }
        }
    }

    return true; // If all checks pass, the number is valid
}

// Generate full Sudoku board using backtracking
bool generateboard(int numberboard[][9], int row, int col) {
    // Check if all rows are filled
    if (row == 8 && col == 9) {
        return true;
    }

    // Move to the next row if the current column is filled
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
    random_device rd;           // Seed for the random number generator
    mt19937 g(rd());            // Mersenne Twister random number generator
    shuffle(numbers, numbers + 9, g); // Shuffle the array

    // Try filling the position with shuffled numbers
    for (int i = 0; i < 9; i++) {
        int number = numbers[i]; // Get the next shuffled number
        if (checkvalid(numberboard, number, row, col)) {
            numberboard[row][col] = number; // Place the number
            if (generateboard(numberboard, row, col + 1)) {
                return true; // If successful, return true
            }
            // Backtrack if placing the number leads to no solution
            numberboard[row][col] = 0;
        }
    }

    return false; // Trigger backtracking if no number fits
}

// Display the Sudoku board
void displayboard(int numberboard[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << numberboard[i][j] << " ";
        }
        cout << endl;
    }
}

// Main function to test the Sudoku board generation
int main() {
    int numberboard[9][9] = {0}; // Initialize the board with zeros

    if (generateboard(numberboard, 0, 0)) {
        cout << "Generated Sudoku Board:" << endl;
        displayboard(numberboard);
    } else {
        cout << "Failed to generate Sudoku board." << endl;
    }

    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Load game function
void load_game(int sudoku[][9], vector<string> &board) {
    string filename = "game_save.txt";
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                file >> sudoku[i][j];
            }
        }
        file.close();
        formatting(board, sudoku);
        cout << "Successfully loaded." << endl;
        for (string &line : board) {
            cout << line << endl;
        }
    } else {
        cout << "Unable to open the file." << endl;
    }
}

// Add a number to the board
void add(int row, int column, int number, int sudoku[][9], vector<string> &board, const bool fixedBoard[][9]) {
    if (row < 0 || row >= 9 || column < 0 || column >= 9) {
        cout << "This position is invalid!" << endl;
        return;
    }
    if (fixedBoard[row][column]) {
        cout << "This position is fixed and cannot be modified!" << endl;
        return;
    }
    if (number < 1 || number > 9) {
        cout << "Your number is out of range!" << endl;
        return;
    }

    // Update the board
    sudoku[row][column] = number;
    formatting(board, sudoku);
    for (string &line : board) {
        cout << line << endl;
    }
}

// Remove a number from the board
void removing(int row, int column, int sudoku[][9], vector<string> &board, const bool fixedBoard[][9]) {
    if (row < 0 || row >= 9 || column < 0 || column >= 9) {
        cout << "This position is invalid!" << endl;
        return;
    }
    if (fixedBoard[row][column]) {
        cout << "This position is fixed and cannot be modified!" << endl;
        return;
    }
    sudoku[row][column] = 0;
    formatting(board, sudoku);
    for (string &line : board) {
        cout << line << endl;
    }
}

// Save the board
void save(int sudoku[][9]) {
    string filename = "game_save.txt";
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                file << sudoku[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Game saved to " << filename << endl;
    } else {
        cout << "Unable to open file for saving." << endl;
    }
}

// Validate the player's board
bool validate_board(int sudoku[][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int num = sudoku[row][col];
            if (num == 0) continue;

            // Temporarily remove the number from the board
            sudoku[row][col] = 0;

            // Check for duplicates in the row, column, and 3x3 grid
            for (int i = 0; i < 9; i++) {
                if (sudoku[row][i] == num || sudoku[i][col] == num) {
                    sudoku[row][col] = num;
                    return false;
                }
            }

            int startRow = (row / 3) * 3;
            int startCol = (col / 3) * 3;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (sudoku[startRow + i][startCol + j] == num) {
                        sudoku[row][col] = num;
                        return false;
                    }
                }
            }

            // Restore the number
            sudoku[row][col] = num;
        }
    }
    return true;
}

// Check if the game is complete
bool check_completion(int sudoku[][9], const int solution[][9]) {
    // Check if the board matches the solution
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != solution[i][j]) {
                return false;
            }
        }
    }
    return true;
}


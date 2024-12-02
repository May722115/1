#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

vector<vector<int>> board(9, vector<int>(9, 0)); 
vector<vector<int>> sudoku(9, vector<int>(9, 0)); 
string filename = "game_save.txt"; 
string answer_file = "answer.txt";

//display the board for playing
void display_board() {
    cout << "   1 2 3   4 5 6   7 8 9" << endl;
    cout << " +-------+-------+-------+" << endl;
    for (int i = 0; i < 9; i++) { //row
        cout << char('A' + i) << "| "; 
        for (int j = 0; j < 9; j++) { //column
            cout << (board[i][j] == 0 ? '.' : to_string(board[i][j])) << " ";
            if ((j + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((i + 1) % 3 == 0) cout << " +-------+-------+-------+" << endl;
    }
}

//load game function: strart the game
void load_game() {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < SIZE; j++) {
                file >> sukudo[i][j]; // Read the number into the board
            }
        }
        file.close();
        formatting (board, sudoku);
        cout << "Suscessfully loaded" << endl;
        display_board(); 
    } else {
        cout << "This file is unable to open qAq" << endl;
    }
}

//add a number to the board
void add(int row, int column, int number) {
    if (row < 0 || row >= 9|| column < 0 || column >= 9) {  //invalid position
        cout << "This position is invalid!" << endl;
        return;
    }
    if (sudoku[row][column] != 0) { //filled position
        cout << "This position already filled!" << endl;
        return;
    }
    if (number < 1|| number > 9){ //input out of range
        cout << "Your number is out of range!"<< endl;
        return;
      
    board[row][column] = number; //normal input
    formatting(board, sukudo);
    display_board();
}

//remove a number from the board
void remove(int row, int column) {
    if (row < 0 || row >= 9 || column < 0 || column >= 9) { //invalid position
        cout << "This position is invalid!" << endl;
        return;
    }
    sukudo[row][column] = 0; 
    formatting(board, sukudo);
    display_board();
}

//save the baord
void save() {
    ofstream file(filename);
    if (file.is_open()) { //save board to file
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

// Check if the game is complete
void check_completion() {
    ifstream file(answer_file);
    if (!file.is_open()) {
        cout << "Unable to open answer file." << endl;
        return;
    }

    vector<vector<int>> answer(9, vector<int>(9, 0));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            file >> answer[i][j]; // Read the correct answer
        }
    }
    file.close();

    bool complete = true;
    for (int i = 0; i < 9 && complete; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != answer[i][j]) {
                complete = false;
                break;
            }
        }
    }

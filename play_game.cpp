#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

vector<vector<int>> board(9, vector<int>(9, 0)); 
string filename = "game_save.txt"; 

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

//add a number to the board
void add(int row, int column, int number) {
    if (row < 0 || row >= 9|| column < 0 || column >= 9) {  //invalid position
        cout << "This position is invalid!" << endl;
        return;
    }
    if (board[row][column] != 0) { //filled position
        cout << "This position already filled!" << endl;
        return;
    }
    if (number < 1|| number > 9){ //input out of range
        cout << "Your number is out of range!"<< endl;
        return;
      
    board[row][column] = number; //normal input
    display_board();
}

//remove a number from the board
void remove(int row, int column) {
    if (row < 0 || row >= 9 || column < 0 || column >= 9) { //invalid position
        cout << "This position is invalid!" << endl;
        return;
    }
    board[row][column] = 0; 
    display_board();
}

//save the baord
void save() {
    ofstream file(filename);
    if (file.is_open()) { //save board to file
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                file << board[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Game saved to " << filename << endl;
    } else {
        cout << "Unable to open file for saving." << endl;
    }
}

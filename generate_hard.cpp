#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "generate_hard.h"

using namespace std;

//declare and initialize board and numberborad for storing
vector<string> board;
int numberboard[9][9] = {0};

//Check for validity of value generated at each position
bool checkvalid(int numberboard[][9], int number, int row, int col) {
    //check whether the number already exists in the colunms
    for (int i = 0; i < 9; i++) {
        if (numberboard[row][i] == number) {
            return false;
        }
    }

    //check whether the number already exists in the rows
    for (int i = 0; i < 9; i++) {
        if (numberboard[i][col] == number) {
            return false;
        }
    }

    //check whether the number already exists in the 3x3 matrix
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
    //check whether all rows are filled, exit if all filled
    if (row == 8 && col == 9) {
        return true;
    }

    //check whether all colunms in the row are filled, change a row if all filled
    if (col == 9) {
        row++;
        col = 0;
    }

    //check whether the position is filled, if filled, change to another colunm
    if (numberboard[row][col] != 0) {
        return generateboard(numberboard, row, col + 1);
    }

    //fill the number in each colunm of a row
    for (int i = 1; i <= 9; i++) {
        //randomly generateing a number from 1 to 9
        int number = rand() % 9 + 1;
        //check if the number if valid and fill it in the position if valid
        if (checkvalid(numberboard, number, row, col)) {
            numberboard[row][col] = number;
            //check whether next valid number exists, back to previous step if not
            if (generateboard(numberboard, row, col + 1)) {
                return true;
            }
            numberboard[row][col] = 0;
        }
    }
    return false;
}

//check whether the number want to be removed exists
bool checkremain(int numberboard[][9], int row, int col){
    //check for column
    for (int i = 0; i < 9; i++){
        if (numberboard[row][i] != 0){
            return true;
        }
    }

    //check for row
    for (int i = 0; i < 9; i++){
        if (numberboard[i][col] != 0){
            return true;
        }
    }

    //check for 3x3 matrix
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (numberboard[(row / 3 * 3) + i][(col / 3 * 3) + j] != 0){
                return true;
            }
        }
    }
    return false;
}

//remove certain amount of number for the problem
void removehard(int numberboard[][9]){
    int number, count = 0, row, col;
    int countl[9] = {0};
    //randomly chosen a number to remove completely
    number = rand() % 9 + 1;

    //Remove all chosen number for hard version
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (numberboard[i][j] == number){
                numberboard[i][j] = 0;
            }
        }
    }
    //Count number of digits removed
    count += 9;
    countl[number-1] = 9;

    //Remove 50 numbers in total
    while (count < 50){
        //randomly choose a position
        row = rand() % 9;
        col = rand() % 9;
        //check whether the chosen number have been removed and ensure removed number will not make solution unsovlable
        if (numberboard[row][col] != 0 && checkremain(numberboard, row, col) && countl[numberboard[row][col]-1] < 6){
            //remove the valid number and count 
            numberboard[row][col] = 0;
            count += 1;
            countl[numberboard[row][col] - 1] += 1;
        }
    }
}

//read game board format from file board.txt
void formgameboard(vector<string> &board) {
    string line;
    //open the file
    ifstream fin("board.txt");

    //Announce if fail to open
    if (fin.fail()) {
        cout << "Something went wrong! Please ask designers to upload the board." << endl;
        exit(1);
    }

    //read line by line and store in a vector
    while (getline(fin, line)) {
        board.push_back(line);
    }

    fin.close();
}

//fill in the generated problems into the board format
void formatting(vector<string> &board, int numberboard[][9]){
    int row = 0, col = 0;
    char digit;

    //read each line in the format, change . to number hints if not removed
    for (string &line : board){
        for (int i = 0; i < line.size(); i++){
            //check if the current character is the position for number hint
            if (line[i] == '.'){
                //replace number to . if the number is not 0, which means a removed answer
                if (numberboard[row][col] != 0){
                    digit = numberboard[row][col] + '0';
                    line[i] = digit;
                }
                //check whether it is the last column in a row, change to another column if not and change to a new row if yes
                if (col < 9){
                    col += 1;
                }
                if (col == 9){
                    row += 1;
                    col = 0;
                }
            }
        }
    }
}

//store generated full board as external file for later answer checking
void storeanswer(int numberboard[][9]){
    //create an external file for storage
    ofstream fout("answer.txt");
    //cout if fail to open
    if (fout.fail()){
        cout << "Error, try again." << endl;
        exit(1);
    }
    //store the answer to external file
    for (int j = 0; j < 9; j++){
        for (int k = 0; k < 9; k++){
            fout << numberboard[j][k] <<" ";
        }
        fout << endl;
    }
    //close file
    fout.close();
}

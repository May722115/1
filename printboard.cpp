#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

//Read board format from board.txt
void formgameboard(vector<string> &board){
    //Declaring string line
    string line;

    //Read the board format from the file board.txt
    ifstream fin;
    fin.open("board.txt");

    //check if board.txt exists
    if ( fin.fail() ){
        cout << "Something wrong! Please ask designers to upload the board." << endl;
        exit(1);
    }
    //read board.txt line by line and store the lines in a vector
    while (getline(fin, line)){
        board.push_back(line);
    }
    //close the file
    fin.close();
}

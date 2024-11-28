#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

//add a number to the board
void add(int row, int column, int number){
  if (row< 0|| row>= size|| column>= size){
    cout<< "The position is invalid!"<< endl;
    return;
  }
  if (board[row][column] != 0){
    cout<< "This position had alrewady filled!"<<endl;
    return;
  }
  board[row][column] = number;
  display_board();
}

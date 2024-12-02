#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "generate_hard.h"
#include "generate_function.h"
using namespace std;

int main()
{   int sudoku[9][9]={0};
    int sudoku_copy[9][9]={0};
    vector<string> board;
    
    while(true){
        srand(time(0));
        cout<<"Type \"play\" to start a playing a game"<<endl;
        cout<<"Type \"exit\" to exit the programm"<<endl;
        cout<<"Type \"records\" to show the records of the games"<<endl;
        string input;
        cin>>input;
        if(input == "play"){
            play_game(sudoku, sudoku_copy, board) 
            /*1.This function is a void function. 
              
              2.It first ask user to choose start a new game to load previous one.
              
              3.If user choose to start a new one ask user to input a difficulty level.Then a new game is randomly generated accordingly(maybe use 2D array)
              (use an extra function for this step). The answer should be save as soon as a new game is generated or old one is loaded for future comparision.
              
              3.A timer should be set up to record.
             
              4.Then the user input "add", "remove", "quit" or "save".
                
                add,remove: add or remove a number in a specific place by editing the array.
                
                quit: back to the main menu. Stop the timer. Add a record to the file.
                
                save: save the current game to a file. 
                It there is already a file with the same name, the new file should replace the old one
              
              5.Whenever the user input "add", check whether the game is complete. If yes, print a message and back to the main menu.
            */

        }

        else if(input == "record"){

            record()
            /* This function is a void function it opens the file for records and print it on the screen. The information should be sorted properly*/
        }
        else if(input == "exit"){
            break;
        }
        else{
            cout<<"Please enter a valid input"<<endl;
        }

    }
    return 0;
}

void load_game(int sudoku [][9], int sudoku_copy[][9], vector<string> &board) {
    ifstream file("board.txt");
    if (!file) {
        cout << "No saved game found. Please start a new game." << endl;
        return;
    }

    string line;
    int row = 0;
    while (getline(file, line) && row < 9) {
        for (int col = 0; col < 9 && col < line.length(); ++col) {
            if (isdigit(line[col])) {
                sudoku[row][col] = line[col] - '0';
            } else {
                sudoku[row][col] = 0;
            }
        }
        ++row;
    }
    file.close();

    std::memcpy(sudoku_copy, sudoku, sizeof(int) * 9 * 9);
    formatting(board, sudoku);
    cout << "Loaded Game Board:" << endl;
    for (string &line : board) {
        cout << line << endl;
    }
}

void save(const int sudoku[][9], int elapsedTime) {
    ofstream file("board.txt");
    if (!file) {
        cout << "Failed to save the game." << endl;
        return;
    }

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (sudoku[row][col] == 0) {
                file << ".";
            } else {
                file << sudoku[row][col];
            }
        }
        file << endl;
    }
    file.close();

    ofstream recordFile("records.txt", ios::app);
    if (!recordFile) {
        cout << "Failed to save time record." << endl;
        return;
    }
    recordFile << "Time: " << elapsedTime << " seconds" << endl;
    recordFile.close();
    cout << "Game and record saved successfully!" << endl;
}

void play_game(int sudoku[][9],int sudoku_copy[][9], vector<string> board){
    string input2;
    cin>>input2;      
    while(input2!="new" || input2!="load"){
        cout<<"Please enter \"new\" or \"load\"."<<endl;
        cin>>input2;
    }    
    if(input2 == "new"){
            int level;
            cout<<"Please enter number 1-3 to choose difficulty level";
            cin>>level;
            while(level!=1 || level!=2 || level!=3){
                cout<<"please enter a valid input"<<endl;
                cin>>level;
            }
            formgameboard(board);
            generateboard(sudoku, 0, 0);
            std::memcpy(sudoku_copy, sudoku, sizeof(sudoku));
            storeanswer(sudoku);
            if(level==1){
                removeElements(sudoku, sudoku_copy, 20, 1); 

            }
            else if(level==2){
                removeElements(sudoku, sudoku_copy, 35, 2);
            }
            else{
            removehard(sudoku);
            }
            
            formatting(board, sudoku);

        for (string &line : board) {
        cout << line << endl;
        }

            

        }
    else if(input2 == "load"){

            load_game()
                    
            /* This function take the file saved before for user to play*/
        }

    //following part starts when a game is prepared and user begins to play.    

    string input3;
    cin>>input3;
    while (input3 !="quit"){  
        // add a number to the board, check whether it is correct
        if(input3 == "add"){
            int row, column, number;
            cout << "Enter row(A-I), column(1-9), number(1-9): "<<endl;
            cin >> row>> column>> number;
            add(row -'A',column -1,number)//user fill in a number

            check()//check whether the game is complete. If yes, quit and stop the timer. Add the time record to the file(use another function).
            cin>>input3;
            
        }
        // remove a number from the board
        else if(input3 == "remove") {
            int row, column;
            cout << "Enter row(A-I), column(1-9): "<<endl;
            cin >> row>> column;          
            remove(row - 'A',column -1)//remove a number
            cin>>input3;

        }
        // save the board
        else if(input3 == "save"){
            save()//save the game to a file
        }
        else {
            cout<<"Please enter a valid input"<<endl;
            cin>>input3; 
        }
    }
}

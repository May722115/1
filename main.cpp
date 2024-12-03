#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <cstdio>
#include <sys/stat.h>
#include "generate_hard.h"
#include "generate_function.h"
#include "play_game.h"
using namespace std;

struct Record {
    int level;
    double time;
};

bool fileExists(const string &filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

void showrecords() {
    ifstream file("records.txt");
    if (!file) {
    cout << "No records found" << endl;
    return;
}
    string line;
    cout << "Game Records:" << endl;
    while (getline(file, line)) { 
        cout << line << endl; 
    }
    file.close();
}

void record(const string &level, double time) {
    vector<Record> records;

    // Check if there is a current record, and if none, create record
    if (fileExists("record.txt")) {
        ifstream file("record.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                Record rec;
                iss >> rec.level >> rec.time;
                records.push_back(rec);
            }
            file.close();
        }
    }

    // Adding new record
    records.push_back({level, time});

    // Sorting by time
    sort(records.begin(), records.end(), [](const Record &a, const Record &b) {
        return a.time < b.time;
    });

    ofstream outfile("record.txt");
    for (const auto &rec : records) {
        outfile << rec.level << " " << rec.time << endl;
    }

    // Display updated records
    cout << "---- Game Records ----" << endl;
    for (const auto &rec : records) {
        cout << "Level: " << rec.level << ", Time: " << rec.time << " seconds" << endl;
    }
    cout << "----------------------" << endl;
}

void play_game(int sudoku[][9],int sudoku_copy[][9], vector<string> board);

int main(){   
    int sudoku[9][9]={0};
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
            play_game(sudoku, sudoku_copy, board); 
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

            showrecords();
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

void play_game(int sudoku[][9],int sudoku_copy[][9], vector<string> board){
    int size[0][0] = {0};
    string input2;
    int level;
    cin>>input2;      
    while(input2!="new" || input2!="load"){
        cout<<"Please enter \"new\" or \"load\"."<<endl;
        cin>>input2;
    }    
    auto start = std::chrono::high_resolution_clock::now();
    if(input2 == "new"){
            const char* filename1 = "answer.txt";
            const char* filename2 = "save_game.txt";
            remove(filename1);
            remove(filename2);
            cout<<"Please enter number 1-3 to choose difficulty level";
            cin>>level;
            while(level!=1 || level!=2 || level!=3){
                cout<<"please enter a valid input"<<endl;
                cin>>level;
            }
            formgameboard(board);
            generateboard(sudoku, 0, 0);
            std::memcpy(sudoku_copy, sudoku, sizeof(size));
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

            load_game(sudoku, board);
                    
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
            add(row -'A',column -1,number, sudoku, board);//user fill in a number

            if(check(sudoku)){
                cout<<"Congradulation! You get the corrent answer!"<<endl;
                auto end = std::chrono::high_resolution_clock::now();
                chrono::duration<double> duration = end - start;
                record(level, duration.count());
                
                break;
            }//check whether the game is complete. If yes, quit and stop the timer. Add the time record to the file(use another function).
            cin>>input3;
            
        }
        // remove a number from the board
        else if(input3 == "remove") {
            int row, column;
            cout << "Enter row(A-I), column(1-9): "<<endl;
            cin >> row>> column;          
            removing(row - 'A',column -1, sudoku, board);//remove a number
            cin>>input3;

        }
        // save the board
        else if(input3 == "save"){
            save(sudoku);//save the game to a file
        }
        else {
            cout<<"Please enter a valid input"<<endl;
            cin>>input3; 
        }
    }
}

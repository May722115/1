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
    int level = -1; 
    double time = 0.0;

    Record(int lvl, double t) : level(lvl), time(t) {}
    Record() = default;
};

bool fileExists(const string &filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}
void removePlaceholderIfNecessary();

void showrecords() {
    ifstream file("game_records.txt");
    if (!file) {
        cout << "-------------------- Game Records --------------------" << endl;
        cout << "We couldn't find any record. Play a game to start!" << endl;
        cout << "------------------------------------------------------" << endl;
        return;
    }

    string line;
    vector<string> records; 
    bool hasValidRecords = false;

    while (getline(file, line)) {
        istringstream iss(line);
        int level;
        double time;

        if (iss >> level >> time && level > 0) {
            records.push_back("Level: " + to_string(level) + " | Time: " + to_string(time) + " seconds");
            hasValidRecords = true;
        }
    }
    file.close();

    if (hasValidRecords) {
        cout << "-------------------- Game Records --------------------" << endl;
        for (const auto &record : records) {
            cout << record << endl;
        }
        cout << "------------------------------------------------------" << endl;

        removePlaceholderIfNecessary();
    } else {
        cout << "-------------------- Game Records --------------------" << endl;
        cout << "We couldn't find any record. Play a game to start!" << endl;
        cout << "------------------------------------------------------" << endl;
    }
}

void removePlaceholderIfNecessary() {
    ifstream file("game_records.txt");
    vector<string> lines;
    bool placeholderRemoved = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("We couldn't find any record. Play a game to start!") != string::npos) {
                placeholderRemoved = true;
                continue; 
            }
            lines.push_back(line);
        }
        file.close();
    }

    // Rewrite the file without the placeholder
    if (placeholderRemoved) {
        ofstream outfile("game_records.txt");
        for (const auto &line : lines) {
            outfile << line << endl;
        }
        outfile.close();
    }
}

void record(const int &level, double time) {
    vector<Record> recordList;

    // Check existing records
    if (fileExists("game_records.txt")) {
        ifstream file("game_records.txt");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                // Skip placeholder message
                if (line.find("We couldn't find any record. Play a game to start!") != string::npos) {
                    continue;
                }

                istringstream iss(line);
                Record recordEntry;

                if (!(iss >> recordEntry.level >> recordEntry.time)) {
                    // Skip invalid records
                    continue;
                }

                recordList.push_back(recordEntry);
            }
            file.close();
        }
    }

    // Add new record
    if (level > 0) { // Only accept valid levels
        recordList.push_back(Record(level, time));
    } else {
        cerr << "Error: Invalid level " << level << ". Record not added." << endl;
    }

    sort(recordList.begin(), recordList.end(), [](const Record &a, const Record &b) {
        return a.time < b.time;
    });

    ofstream outfile("game_records.txt");
    if (outfile.is_open()) {
        // Add header back to the file
        outfile << "-------------------- Game Records --------------------" << endl;

        // Write sorted records
        for (const auto &rec : recordList) {
            outfile << "Level: " << rec.level << " | Time: " << rec.time << " seconds" << endl;
        }

        // Add footer
        outfile << "------------------------------------------------------" << endl;

        outfile.close();
    } else {
        cerr << "Error: Unable to write to game_records.txt." << endl;
    }

    // Display updated records
    cout << "---- Game Records ----" << endl;
    for (const auto &rec : recordList) {
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

        else if(input == "records"){

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
    int size[9][9] = {0};
    string input2;
    int level;
    cout<<"Enter \"new\" to start a new game. Enter \"load\" to load a saved game"<<endl;
    cin>>input2;      
    while(input2!="new" && input2!="load"){
        cout<<"Please enter \"new\" or \"load\"."<<endl;
        cin>>input2;
    }    
    auto start = std::chrono::high_resolution_clock::now();
    if(input2 == "new"){
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    sudoku[i][j]=0;}
            }
            const char* filename1 = "answer.txt";
            const char* filename2 = "save_game.txt";
            remove(filename1);
            remove(filename2);
            cout<<"Please enter number 1-3 to choose difficulty level"<<endl;
            cin>>level;
            while(level!=1 && level!=2 && level!=3){
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
            formgameboard(board);
            load_game(sudoku, board);
                    
            /* This function take the file saved before for user to play*/
        }

    //following part starts when a game is prepared and user begins to play.    
    cout<<"Enter \"add\" to fill in a number"<<endl;
    cout<<"Enter \"remove\" to remove a number"<<endl;
    cout<<"Enter \"save\" to same the current game. Note: it will cover the previously saved game."<<endl;
    cout<<"Enter \"quit\" to quit the game"<<endl;
    string input3;
    cin>>input3;
    while (input3 !="quit"){  
        // add a number to the board, check whether it is correct
        if(input3 == "add"){
            int column, number;
            char row;
            cout << "Enter row(A-I), column(1-9), number(1-9): "<<endl;
            cin >> row>> column>> number;
            if(row>='A' && row<='I' && column>=1 && column<=9 && number>=1 && number<=9){
            add(row -'A',column -1,number, sudoku, board);//user fill in a number

                if(check_completion(sudoku)){
                    cout<<"Congratulation! You get the correct answer!"<<endl;
                    auto end = std::chrono::high_resolution_clock::now();
                    chrono::duration<double> duration_raw = end - start;
                    double duration=duration_raw.count();
                    string filename = "time.txt";
                    double time_taken = 0;
                    ofstream outputFile;
                    outputFile.open(filename, ios::app);
                    if (!outputFile) {
                    cout << "Error for saving time taken." << endl;
            
                    }
                    outputFile << duration<<" ";
                    outputFile.close();
                    ifstream inputFile(filename);
                    if (!inputFile) {
                    cout << "Error opening file for time taken." << endl; // Return an error code
                    }
                    double value;
                    while(inputFile>>value){
                        time_taken+=value;
                    }
                    inputFile.close();
                    record(level, time_taken);
                
                
                    break;}
            //check whether the game is complete. If yes, quit and stop the timer. Add the time record to the file(use another function).
                cout<<"Enter \"add\" to fill in a number"<<endl;
                cout<<"Enter \"remove\" to remove a number"<<endl;
                cout<<"Enter \"save\" to same the current game. Note: it will cover the previously saved game."<<endl;
                cout<<"Enter \"quit\" to quit the game"<<endl;
                cin>>input3;}
            
            else{
                cout<<"Your input is not valid. Choose add, remove, save, quit again!"<<endl;
                cin>>input3;
            }
            
        }
        // remove a number from the board
        else if(input3 == "remove") {
            char row;
            int column;
            cout << "Enter row(A-I), column(1-9): "<<endl;
            cin >> row>> column;          
            if(row>='A' && row<='I' && column>=1 && column<=9){
                removing(row - 'A',column -1, sudoku, board);//remove a number
                cout<<"Enter \"add\" to fill in a number"<<endl;
                cout<<"Enter \"remove\" to remove a number"<<endl;
                cout<<"Enter \"save\" to same the current game. Note: it will cover the previously saved game."<<endl;
                cout<<"Enter \"quit\" to quit the game"<<endl;
                cin>>input3;
            
            }
            else{
                cout<<"Your input is not valid. Choose add, remove, save, quit again!"<<endl;
            
            cin>>input3;}

        }
        // save the board
        else if(input3 == "save"){
            save(sudoku);//save the game to a file
            auto pause = std::chrono::high_resolution_clock::now();
            chrono::duration<double> duration2_raw = pause - start;
            double duration2=duration2_raw.count();
            string filename = "time.txt";
            ofstream outputFile;
            outputFile.open(filename, ios::app);
            if (!outputFile) {
            cout << "Error for saving time taken." << endl;
            
            }
            outputFile << duration2<<" ";
            outputFile.close();

            break;
        }
        else {
            cout<<"Please enter a valid input from add, remove, save or quit"<<endl;
            cin>>input3; 
        }
    }
}

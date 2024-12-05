
void play_game();

int main(){

    while(true){
        srand(time(0));
        cout<<"Type \"play\" to start a playing a game"<<endl;
        cout<<"Type \"exit\" to exit the programm"<<endl;
        cout<<"Type \"records\" to show the records of the games"<<endl;
        string input;
        cin>>input;
        if(input == "play"){
            play_game();
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

void play_game(){
    int size[9][9] = {0};
    string input2;
    int level;
    int sudoku[9][9]={0};
    int sudoku_copy[9][9]={0};
    vector<string> board;
    cout<<"Enter \"new\" to start a new game. Enter \"load\" to load a saved game"<<endl;
    cin>>input2;
    while(input2!="new" && input2!="load"){
        cout<<"Please enter \"new\" or \"load\"."<<endl;
        cin>>input2;
    }
    auto start = std::chrono::high_resolution_clock::now();
    if(input2 == "new"){
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
            srand(time(0));
            formgameboard(board);
            generateboard(sudoku, 0, 0);
            std::memcpy(sudoku_copy, sudoku, sizeof(size));
            storeanswer(sudoku);
            for(int i = 0; i < 9; i++){
                for(int j = 0; j < 9; j++){
                    cout << sudoku[i][j];
                }
                cout << endl;
            }
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
                    cout<<"Congradulation! You get the corrent answer!"<<endl;
                    auto end = std::chrono::high_resolution_clock::now();
                    chrono::duration<double> duration = end - start;
                    record(level, duration.count());


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
        }
        else {
            cout<<"Please enter a valid input from add, remove, save or quit"<<endl;
            cin>>input3;
        }
    }
}

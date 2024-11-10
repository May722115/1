#include <iostream>
#include <string>

using namespace std;

int main()
{
    
    while(true){
        cout<<"Type \"play\" to start a playing a game"<<endl;
        cout<<"Type \"exit\" to exit the programm"<<endl;
        cout<<"Type \"records\" to show the records of the games"<<endl;
        string input;
        cin>>input;
        if(input == "play"){
            
            play_game() 
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
            cin>>input;
        }

    }
    return 0;
}


void play_game(){
    string input2;
    cin>>input2;      
        if(input2 == "new"){
            string level;
            cin>>level;
            generate_game(level)
            /* This function generate a new game for user depending on level chosed.*/

        }
        else if(input2 == "load"){

            load_game()
            /* This function take the file saved before for user to play*/
        }

    //following part starts when a game is prepared and user begins to play.    

    string input3;
    cin>>input3;
    while (input3 !="quit"){   
        if(input3 == "add"){

            add(row,column,number)//user fill in a number

            check()//check whether the game is complete. If yes, quit and stop the timer. Add the time record to the file(use another function).
            
        }
        else if(input3 == "remove") {

            remove(row,column)//remove a number

        }
        else if(input3 == "save"){

            save()//save the game to a file
        }
        else {
            cout<<"Please enter a valid input"<<endl;
            cin>>input3; 
        }
    }
}

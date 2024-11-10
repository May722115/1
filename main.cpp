#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout<<"Type \"new\" to start a new game"<<endl;
    cout<<"Type \"Load\" to load the game saved before"<<endl;
    cout<<"Type \"exit\" to exit the programm"<<endl;

    string input;
    cin>>input;
    while(input != "exit"){
        if(input == "new"){
            
            new_game() 
            /*1.This function is a void function. 
              
              2.It first ask user to input a difficulty level.Then a new game is randomly generated accordingly(maybe use 2D array)
              (use an extra function for this step). The answer should be save for future comparision.
              
              3.A timer should be set up to record.
             
              4.Then the user input "add", "delete", "quit" or "save".
                
                add,delete: add or remove a number in a specific place by editing the array.
                
                quit: back to the main menu. Stop the timer
                
                save: save the current game to a file. 
                It there is already a file with the same name, the new file should replace the old one
              
              5.Whenever the user input "add", check whether the game is complete. If yes, print a message and back to the main menu.
            */

        }
        else if(input == "load"){

            load_game()
            /* This function is a void function it loads the game saved before for user to play and directly jump to step 3 in new_game().*/
        }

    }

    return 0;
}

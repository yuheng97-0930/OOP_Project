#ifndef MENU_H
#define MENU_H


#include <iostream>
#include <sstream>
#include "Utils.h"
#include "GameMode.h"
#include "SingleMode.h"
#include "MultiplayerMode.h"
#include <cstdlib> // for exit()

/*
    Menu class for managing the main interface of the game.
    Allows users to choose game modes, start a new game, or exit.
 */
class Menu{
private:
    int choose;
    string input;
    
public:
    void NewGame();     // Starts a new game by selecting a mode
    void exit();        // Prompts user to confirm and exit the game
    void displayMenu(); // Displays the main menu loop
};

/*
    Starts a new game session by letting the user select a game mode.
    Uses polymorphism via GameMode* to handle different game modes.
 */
void Menu::NewGame(){
    GameMode* mode = nullptr;
    
    cout<<line(60)<<"\nMode Options:\n"<<line(60)<<endl;
    cout<<"1. Single Mode\n2. Multiplayer Mode"<<endl;

    do{input = isBlankInput("Enter your choose: ");
        stringstream ss(input);
        ss>>choose;
        if(choose ==1){
            clear_line(10);
            cout<<line(60)<<"\nSingle Mode:\n"<<line(60)<<endl;
            mode = new SingleMode();
            break;
        }
        else if(choose ==2){
            clear_line(10);
            cout<<line(60)<<"\nMultiplayer Mode:\n"<<line(60)<<endl;
            mode = new MultiplayerMode();
            break;
        }
        else{
            cout<<"Invalid input. Please try again. (1/2)"<<endl;
            waitAndClearError(2);
        }
    }while(true);
    mode->startGame(); // Polymorphic call to start the selected game mode
    delete mode;       // Free dynamically allocated memory
}

/*
    Prompts the user to confirm exit. Exits the program if confirmed.
 */
void Menu::exit(){
char confirm;

    while (true) {
        input = isBlankInput("Are you sure you want to exit the game? (Y/N): ");
        stringstream ss(input);
        ss >> confirm;
        confirm = toupper(confirm);

        if (confirm == 'Y') {
            cout << "Thank you for playing. Goodbye!\n";
            wait(2);
            ::exit(0); // Ends the program
        } else if (confirm == 'N') {
            cout << "Returning to menu...\n";
            wait(2);
            clear_line(20);
            break;
        } else {
            cout << "Invalid input. Please enter Y or N.\n";
            waitAndClearError(2);
        }
    }
}

/*
    Displays the main menu and handles user interaction.
    Allows the user to choose between starting a new game or exiting.
 */
void Menu::displayMenu() {

    do {
        cout << "           ________________            "<<endl;
        cout << "          /                \\          "<<endl;
        cout << "         {  @         @     }          "<<endl;
        cout << "          [       !        ]           "<<endl;
        cout << "          [_____====+______]           "<<endl;
        cout << "========== HANGMAN MENU ==========\n";
        cout << "1. New Game\n";;
        cout << "5. Exit\n";
        input = isBlankInput("Enter your choice: ");
        stringstream ss(input);
        ss>>choose;
        switch (choose) {
            case 1: 
                clear_line(20);
                NewGame(); 
                break;
            case 5:
                exit();
                break; 
            default:
                cout << "Invalid choice. Try again."<<endl;
                waitAndClearError(20);
        }
    } while (true);
}

#endif //MENU_H
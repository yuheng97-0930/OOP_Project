#ifndef GAME_H
#define GAME_H

#include "Utils.h"           // Assumed to provide helper functions like input and screen clearing
#include "Word.h"            // Contains logic for handling the word guessing
#include "CategoryManager.h" // Manages the list of categories and words
#include <iostream>
#include <string>
#include <sstream>

class Game{
private:
    const int heart =4; //Initial number of lives

public:
    // Displays an ASCII dog character depending on how many hearts (lives) remain
    void displayDog(int State) {
    if (State >= 4) {
        cout << "             (  o   O  )" << endl; // Happy dog
        cout << "           ___\\   ^   /___\n" << endl;
        
    } else if (State >= 3) {
        cout << "             (  o   o  )" << endl; // Worried dog
        cout << "           ___\\   ~   /___\n" << endl;
    } else if(State >=2){
        cout << "             (  o   -  )" << endl; // Hurt dog
        cout << "           ___\\   _   /___" << endl;
        cout << "                          "<<endl;
    }
    else if(State >=1){
        cout << "             (  x   -  )" << endl; // Very hurt
        cout << "           ___\\   _   /___" << endl;
        cout << "                  U        "<<endl;
    }
    else{
        cout << "             (  x   x  )" << endl; // dead & Game over
        cout << "           ___\\   _   /___" << endl;
        cout << "                   U        "<<endl;
    }
}
    // Function to handle the guessing gameplay for a given word
    void guesses(string words);

};
// Implementation of the guessing logic
void Game::guesses(string words){
    Word w(words); // Create a Word object with the secret word
    string guess;
    int wrong =0;
    int Heart = heart;
    char temp;
    do{cout<<"Heart: "<<Heart<<endl;
        displayDog(Heart);
        cout << "Word: " << w.getRevealedWord() << endl;
        // Get player's input
        guess = isBlankInput("Enter your guess:");
        // Only allow single character guesses
        if(guess.length() != 1){
            cout<<"Each guess is limited to a letter."<<endl;
            waitAndClearError(7); // Wait and clear screen
            continue;
        }

        stringstream ss(guess);
        if ((ss>>temp) && w.checkGuess(temp)) {
            cout << "Correct guess!" << endl;
            
        } else {
            cout << "Wrong guess." << endl;
            wrong++;
            Heart--;
        }
        // If game is still ongoing, wait and clear screen
        if(heart>wrong && !w.isFullyGuessed()){
            waitAndClear(8);
        }
    }while(heart>wrong && !w.isFullyGuessed());

    // Game result
    if (w.isFullyGuessed()) {
        cout << "Congratulations! You guessed the word: " << w.getSecretWord() << endl;
    } else {
        clear_line(7);
        cout<<"Heart: "<<Heart<<endl;
        displayDog(Heart);
        cout << "Game Over! The word was: " << w.getSecretWord() << endl;

    }
    waitAndClear(20); // Wait and clear screen before ending
}
 
#endif
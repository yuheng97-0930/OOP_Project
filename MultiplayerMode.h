#ifndef MultiplayerMode_H
#define MultiplayerMode_H

#include "Game.h"
#include "Utils.h"
#include "GameMode.h"

// MultiplayerMode class:
// Inherits from Game and defines behavior for two-player mode
// Player 1 sets a secret word and hint; Player 2 tries to guess it.
class MultiplayerMode : public GameMode{
public:
    // Starts the multiplayer game logic
    void startGame()override;

};
// Implementation of MultiplayerMode::startGame()
// Player 1 enters a secret word and a hint; Player 2 tries to guess the word.
void MultiplayerMode::startGame(){
    string WordInput, WordHint;
    // Prompt Player 1 to enter a valid word (no spaces allowed)
    do{WordInput = isBlankInput("P1, Enter a word for P2 to guess: ");
        if(containsSpace(WordInput)){
            cout<<"Invalid word! Spaces are not allowed. Please enter a single word (e.g., 'apple', 'keyboard')."<<endl;
            waitAndClearError(2);
            continue;
        }
        else{break;}
    }while(true);
    // Get hint from Player 1
    WordHint = isBlankInput("P1,Enter a tip for the word: ");
    // Clear the console to prevent Player 2 from seeing the word
    clear_line(2);
    // Start the guessing phase for Player 2
    cout<<"P2, start guess!\n";
    cout<<"Hint: "<<WordHint<<endl;
    // Use the Game class to handle the guessing logic
    Game g;
    g.guesses(WordInput);
}   

#endif
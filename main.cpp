
#include "Player.h"
#include "Menu.h"
#include <iostream>

using namespace std;


int main(){
    Player p;           // Create a Player object (likely stores player info or score)
    Menu m;             // Create a Menu object to handle game mode and navigation
    cg();               // Presumably displays a welcome message or clears screen (defined in Utils.h?)
    p.displayPlayer();  // Show player information or prompt to enter player name
    m.displayMenu();    // Start the menu system (New Game, Exit, etc.)

    return 0;
}
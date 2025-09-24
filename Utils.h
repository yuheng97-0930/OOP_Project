// Utils.h - Utility functions for console-based applications
#ifndef UTILS_H
#define UTILS_H

#include <iostream>  // For standard I/O (cin, cout)
#include <algorithm> // For algorithms like all_of
#include <cctype>    // For character functions like isspace
#include <chrono>    // For time duration (used in wait)
#include <thread>    // For sleep (std::this_thread::sleep_for)

// It's best to avoid this in headers, but used here for simplicity
using namespace std;

/* 
    Clear a number of console lines
    Moves cursor up and clears the line using ANSI escape codes
    round: number of lines to clear
*/
inline void clear_line(int round) {
    for (int i = 1; i <= round; i++) {
        cout << "\033[F\033[K";
    }
}

// Generate a horizontal line string of given length using '-'
inline string line(int length){
    return string(length,'-');
}

// Pause the program for a given number of seconds
void wait(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// Wait for user to press ENTER, then clear given number of lines
inline void waitAndClear(int lines) {
    string ENTER;
    cout << "Enter to next: ";
    getline(cin, ENTER); // Wait for user input (ENTER)
    clear_line(lines);   // Clear the number of lines specified
}

// Show error message, wait for ENTER, and clear lines
inline void waitAndClearError(int lines) {
    cout << "Press ENTER to try again...";
    string _;
    getline(cin, _);       // Wait for ENTER
    clear_line(lines + 1); // +1 to also clear the error prompt line
}

/* 
    Prompt user until they enter a non-blank input
    Returns the valid user input
*/
inline string isBlankInput(const string& prompts) {
    string input;
    do{cout<<prompts;
        getline(cin, input);

        // Check if input is empty or contains only whitespace
        if(input.empty() || all_of(input.begin(), input.end(), ::isspace)){
            cout << "Error: input cannot be empty or blank. Please try again.\n";
            waitAndClearError(2); // Clear the prompt and error line
        }
        else{
            break; // Valid input received
        }

    }while (true);
    
    return input;
}

/*
    Check if a string contains any space characters
    Returns true if it does, false otherwise*/
inline bool containsSpace(const string& word) {
        return word.find(' ') != string::npos;
}
/*LOGO*/
void cg(){
    cout<<"                                                "<<"       / \\__"<<endl;
    cout<<" _   _    _    _   _  ____ __  __    _    _   _ "<<"      (    @\\___"<<endl;
    cout<<"| | | |  / \\  | \\ | |/ ___|  \\/  |  / \\  | \\ | |"<<"      /         O"<<endl;
    cout<<"| |_| | / _ \\ |  \\| | |  _| |\\/| | / _ \\ |  \\| |"<<"     /   (_____/"<<endl;
    cout<<"|  _  |/ ___ \\| |\\  | |_| | |  | |/ ___ \\| |\\  |"<<"    /_____/   U"<<endl;
    cout<<"|_| |_/_/   \\_\\_| \\_|\\____|_|  |_/_/   \\_\\_| \\_|"<<endl;

    cout<<"                                 ____    _    __  __ _____ "<<endl;
    cout<<"                                / ___|  / \\  |  \\/  | ____|"<<endl;
    cout<<"                               | |  _  / _ \\ | |\\/| |  _|  "<<endl;
    cout<<"                               | |_| |/ ___ \\| |  | | |___ "<<endl;
    cout<<"                                \\____/_/   \\_\\_|  |_|_____|"<<endl;

    // Wait for user to press ENTER before proceeding
    cout<<"Press ENTER to start:";
    string ENTER;
    getline(cin, ENTER);
    wait(1);
    clear_line(13);
}

#endif// UTILS_H

#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // For _getch() - only works on Windows
#include <sstream>
#include <iomanip>

using namespace std;

class Player {
private:
    string gmail;
    string username;
    string password;
    string uid;
    string securityQuestion;
    string securityAnswer;
public:
    void verify(); // Verify Gmail format
    string getHiddenInput(const string& prompt);// Input password with masking
    bool registerAccount(); // Register new user
    string generateUID();// Generate unique user ID
    bool login(); // User login
    void forgot_password(); // Handle forgotten password
    string getUsername() { // Return current username
        return username;
    }
    void displayPlayer();
};

/*Verify that Gmail ends with '@gmail.com'*/
void Player::verify(){
    do{gmail = isBlankInput("Enter your email: ");

        if (gmail.size() >= 10 && gmail.substr(gmail.size() - 10) == "@gmail.com") {
            break;
        } 
        else {
            cout << "Invalid gmail format! Must end with @gmail.com.\n";
            waitAndClearError(2);
        }
    }while(true);
}

/*Hide password input using getch()*/
string Player::getHiddenInput(const string& prompt) {
    string passwords;
    char ch;
    do{
        passwords.clear();
        cout << prompt;
        while ((ch = _getch()) != '\r') { // Until Enter is pressed
            if (ch == '\b') { // backspace handling
                if (!passwords.empty()) {
                    passwords.pop_back();
                    cout << "\b \b";
                }
            } else {
                passwords.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        
        string trimmed = passwords;
        trimmed.erase(0, trimmed.find_first_not_of(" \t\r\n"));
        trimmed.erase(trimmed.find_last_not_of(" \t\r\n") + 1); 

        if (trimmed.empty() || containsSpace(passwords)) {
            cout << "Invalid. The password does not allow spaces or blanks. Pleases try again.\n";
            waitAndClearError(2);
        } else {
            return passwords; 
        }
    }while(true);
    
}

/*Generate a UID by counting lines in file*/
string Player::generateUID() {
    ifstream infile("UserDetail.txt");
    int count = 0;
    string line;
    while (getline(infile, line)) {
        if (!line.empty()) count++;
    }
    infile.close();

    stringstream ss;
    ss << setw(7) << setfill('0') << count;
    return ss.str(); // e.g., "0000012"
}

/*Register a new account*/
bool Player::registerAccount() {
    string pwd1, pwd2;
    verify();

    // Check if email already exists
    ifstream infile("UserDetail.txt");
    string line;
    bool GmailExists = false;

    while (getline(infile, line)) {
        istringstream iss(line);
        string existingUID, existingUsername, existingPassword, existingEmail, q, a;
    
        getline(iss, existingUID, '|');
        getline(iss, existingUsername, '|');
        getline(iss, existingPassword, '|');
        getline(iss, existingEmail, '|');
        getline(iss, q, '|'); 
        getline(iss, a); 
        if (existingEmail == gmail) {
            GmailExists = true;
            break;
        }

    }
    infile.close();

    if (GmailExists) {
        cout << "The email has already been registered.\n";
        waitAndClear(20);
        return false;
    }

    username = isBlankInput("Enter username: ");

    do{pwd1 = getHiddenInput("Enter password: ");
        pwd2 = getHiddenInput("Confirm password: ");
        if(pwd1 != pwd2){
            cout << "Passwords do not match. Try again.\n";
            waitAndClearError(3);
        }
    }while(pwd1 != pwd2);
    password = pwd1;

     // Set up security question
    securityQuestion = isBlankInput("Set your security question (e.g. What's your pet's name?): ");
    securityAnswer = isBlankInput("Answer: ");

    uid = generateUID();

    // Save account to file
    ofstream outfile("UserDetail.txt", ios::app);
    if (outfile.is_open()) {
        outfile << uid << "|" << username << "|" << password << "|" << gmail
                << "|" << securityQuestion << "|" << securityAnswer << endl;
        outfile.close();
        cout << "Registration successful! Your UID is: " << uid << endl;
    } else {
        cout << "Error writing to file.\n";
        return false;
    }
    waitAndClear(20);
    return true;
}

/*Log in using UID or Gmail*/
bool Player::login() {
    int attempts = 0;
    bool success = false;

    while (attempts < 3 && !success) {
        string identifier, pwd;

        identifier = isBlankInput("Enter UID or Email: ");
        pwd = getHiddenInput("Enter password: ");

        ifstream infile("UserDetail.txt");
        string line;

        while (getline(infile, line)) {
            istringstream iss(line);
            string fileUID, fileUsername, filePassword, fileEmail, fileQ, fileA;
            getline(iss, fileUID, '|');
            getline(iss, fileUsername, '|');
            getline(iss, filePassword, '|');
            getline(iss, fileEmail, '|');
            getline(iss, fileQ, '|');
            getline(iss, fileA);

            if ((identifier == fileUID || identifier == fileEmail) && pwd == filePassword) {
                username = fileUsername;
                password = pwd;
                cout << "Login successful! Welcome " << username << endl;
                success = true;
                break;
            }
        }
        infile.close();
        
        if (!success) {
            attempts++;
           
            if (attempts < 3) {  
                cout << "Invalid UID/email or password. Please try again.\n";
                waitAndClearError(3);
            }
        }
    }

    if (!success) {
        string input;
        cout << "Too many failed attempts.\n";
        cout << "Forgot password? Enter 1 to reset password, or press Enter to return to menu: ";
        getline(cin, input);

        if (input == "1") {
            clear_line(10);
            cout << line(60) << "\nFORGOT PASSWORD\n" << line(60) << endl;
            forgot_password();
        }

        waitAndClear(20);
        return false;
    }

    waitAndClear(20);
    return true;
}

/*Password reset using UID + security Q&A*/
void Player::forgot_password() {
    string newPwd1, newPwd2;
    uid = isBlankInput("Enter your UID: ");
    gmail = isBlankInput("Enter your email: ");

    ifstream infile("UserDetail.txt");
    ofstream temp("temp.txt");

    string line;
    bool uidFound = false;
    bool success = false;

    while (getline(infile, line)) {
        istringstream iss(line);
        string fileUID, fileUsername, filePassword, fileEmail, fileQ, fileA;
        getline(iss, fileUID, '|');
        getline(iss, fileUsername, '|');
        getline(iss, filePassword, '|');
        getline(iss, fileEmail, '|');
        getline(iss, fileQ, '|');
        getline(iss, fileA);

        if (fileUID == uid) {
            uidFound = true;
            if (fileEmail == gmail) {
                cout << "Security Question: " << fileQ << endl;
                string ans = isBlankInput("Answer: ");

                if (ans != fileA) {
                    cout << "Security answer incorrect.\n";
                    temp << line << endl;
                    continue;;
                }

                do{newPwd1 = getHiddenInput("Enter new password: ");
                    newPwd2 = getHiddenInput("Confirm new password: ");
                    if(newPwd1 != newPwd2){
                        cout << "Passwords do not match. Try again.\n";
                        waitAndClearError(3);
                    }
                }while (newPwd1 != newPwd2);

                if (newPwd1 == filePassword) {
                    cout << "New password cannot be the same as the old password. Reset aborted.\n";
                    waitAndClear(20);
                    temp << line << endl;
                } else {
                    temp << fileUID << "|" << fileUsername << "|" << newPwd1 << "|"
                         << fileEmail << "|" << fileQ << "|" << fileA << endl;
                    cout << "Password successfully reset.\n";
                    waitAndClear(20);
                    success = true;
                }

            } else {
                cout << "Email does not match the UID.\n";
                
                temp << line << endl;

            }
        } else {
            temp << line << endl;
        }
    }

    infile.close();
    temp.close();
    remove("UserDetail.txt");
    rename("temp.txt", "UserDetail.txt");

    if (!uidFound) {
        cout << "UID not found.\n";
        waitAndClear(20);
    }

    if (!success && uidFound) {
        cout << "Password reset failed.\n";
        waitAndClear(20);
    }
}

/*Show main user account menu*/
void Player::displayPlayer(){
    string Input;
    int choice;
    bool exitMenu = false;

    do{cout<<line(60)<<"\nAUTHENTICATION MENU\n"<<line(60)<<endl;
        cout<<"[1] REGISTER\n[2] LOGIN\n";
        cout<<"[3] FORGOT PASSWORD\n[4] EXIT"<<endl;
        Input = isBlankInput("Enter selection:");
            stringstream ss(Input);
            if((ss >> choice) && (choice == 1 || choice == 2 || choice == 3 || choice == 4)){}
            else{
                cout<<"Invalid input. Please enter a number between 1 and 4.\n";
                waitAndClearError(2);
            }
        

        switch (choice)
        {
        case 1:
            clear_line(10);
            cout<<line(60)<<"\nREGISTER ACCOUNT\n"<<line(60)<<endl;
            registerAccount();
            break;
        case 2:
            clear_line(10);
            cout<<line(60)<<"\nLOGIN\n"<<line(60)<<endl;
            if(login()){
                exitMenu =true;
            }
            break;
        case 3:
            clear_line(10);
            cout<<line(60)<<"\nFORGOT PASSWORD\n"<<line(60)<<endl;
            forgot_password();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            exit(0);
            break;
        default:
            clear_line(8);
            break;
        }
    }while(!exitMenu);
    
}

#endif // PLAYER_H
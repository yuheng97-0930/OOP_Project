#ifndef SINGLEMODE_H
#define SINGLEMODE_H

#include "Game.h"
#include "CategoryManager.h"
#include "GameMode.h"


class SingleMode : public GameMode{
private:
    CategoryManager cm;
    

public:
    void startGame()override;
};

void SingleMode::startGame(){
    int choice;
    string tempInput;
    cm.displayCategories();
    vector<string> categoryList = cm.getCategoryNames();

    tempInput = isBlankInput("Enter the number of the category you want: ");
    stringstream ss(tempInput);
    wait(1);
    clear_line(7);
    if ((ss>>choice) && choice < 1 || choice > categoryList.size()) {
        cout << "Invalid choice. Returning to menu...\n";
        wait(2);
        clear_line(15);
        return;
    }

    string selectedCategory = categoryList[choice - 1];

    vector<pair<string, string>> wordList = 
        cm.getWordsWithTipsByCategory(selectedCategory);

    if (wordList.empty()) {
        cout << "No words found in this category.\n";
        return;
    }

    srand(time(0)); // 确保每次运行不一样
    int index = rand() % wordList.size();

    string chosenWord = wordList[index].first;
    string hint = wordList[index].second;

    cout << "Hint: " << hint << endl;
    Game g;
    g.guesses(chosenWord);
    
}

#endif
#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

// CategoryManager class: manages multiple categories of quiz words and their hints
class CategoryManager {
private:
    // Map to store categories and their corresponding list of (word, hint) pairs
    // Key: category name (e.g., "Cars"), Value: list of words and tips
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> categories;


public:
// Constructor: initializes all categories with words and hints
    CategoryManager() {
        categories["Cars"] = {
            {"perodua", "What is a popular Malaysian car brand?"},
            {"ferrari", "Which Italian brand is known for red supercars?"},
            {"proton", "Which company makes the Saga car in Malaysia?"},
            {"honda", "Which Japanese brand makes the Civic?"},
            {"nissan", "Which car brand has a model called 'Skyline'?"}
        };

        categories["Malaysia states"] = {
            {"johor", "Which state is located in the southern part of Peninsular Malaysia?"},
            {"kuantan", "Which city is the capital of Pahang?"},
            {"sabah", "Which state is famous for Mount Kinabalu?"},
            {"perlis", "Which is the smallest state in Malaysia?"},
            {"malacca", "Which state is known for historical sites and A Famosa?"}
        };

        categories["Countries"] = {
            {"australia", "Which country is both a continent and a country?"},
            {"iceland", "Which country is known for volcanoes and hot springs?"},
            {"malaysia", "Which Southeast Asian country has 13 states and 3 federal territories?"},
            {"japan", "Which country is famous for anime and sushi?"},
            {"china", "Which country has the Great Wall?"}
        };

        categories["Animals"] = {
            {"dog", "Which animal is often called man's best friend?"},
            {"cat", "Which pet purrs and loves to chase mice?"},
            {"bird", "Which animal has wings and can fly?"},
            {"bear", "Which large mammal can be found in forests and hibernates?"},
            {"zebra", "Which animal has black and white stripes?"}
        };
    }

    // Returns a list of all available category names
    std::vector<std::string> getCategoryNames() const {
        std::vector<std::string> names;
        for (const auto& pair : categories) {
            names.push_back(pair.first);
        }
        return names;
    }

    // Returns the word-hint pairs for a specific category
    // If the category doesn't exist, returns an empty list
    std::vector<std::pair<std::string, std::string>> getWordsWithTipsByCategory(const std::string& category) const {
        auto it = categories.find(category);
        if (it != categories.end()) {
            return it->second;
        } else {
            return {};
        }
    }

    // Prints all available categories to the console
    void displayCategories() const{
        std::cout <<"Available Categories:\n"<<endl;
        int index =1;
        for (const auto& pair : categories) {
            std::cout <<index++<< ". " << pair.first << std::endl;
        }
    }
};

#endif
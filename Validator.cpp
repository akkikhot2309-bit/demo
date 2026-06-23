#include "Validator.h"

#include <iostream>
 

 

 //int validations
int Validator::getValidInt(std::string prompt) {

    int value;

    while (true) {

        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            

            std::cin.clear();
        
            std::cout << "  Invalid input. Please enter a number.\n";
        }

        else {

            std::cin.ignore();
            return value;

        }
    }
}


//double validation
double Validator::getValidDouble(std::string prompt) {

    double value;

    while (true) {

        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value <= 0) {

            std::cin.clear();
            std::cin.ignore();
            std::cout << "  Invalid input. Please enter a positive number greater than 0.\n";

        }

        else {

            std::cin.ignore();
            return value;

        }

    }
}

// string validation
std::string Validator::getValidString(std::string prompt) {

    std::string value;

    while (true) {

        std::cout << prompt;
        getline(std::cin, value);

        if (value.empty()) {

            std::cin.ignore();
            std::cout << "  Input cannot be empty. Please try again.\n";

        }

        else {
            return value;
        }
    }
}

// date in foramte yyyy-mm-dd
// helper function
bool Validator::isValidDate(std::string date) {


     //of 10 length
    if (date.length() != 10) return false;

    // dashes must be at position 4 and 7
    if (date[4] != '-' || date[7] != '-') return false;

    // all other characters must be digits
    for (int i = 0; i < 10; i++) {

        if (i == 4 || i == 7) continue;

        if (!isdigit(date[i])) return false;

    }

    // month must be 01 to 12
    // string to int 
    // strip 5 to 6
    int month = stoi(date.substr(5, 2));
    if (month < 1 || month > 12) return false;



    // day must be 1 to 31
    int day = stoi(date.substr(8, 2));
    if (day < 1 || day > 31) return false;

    return true;

}

 
std::string Validator::getValidDate(std::string prompt) {

    std::string date;

    while (true) {


        std::cout << prompt;
        std::cin >> date;


        if (!isValidDate(date)) {

            std::cout << "  Invalid date. Please use YYYY-MM-DD format (example: 2026-06-20).\n";

        }


        else {

            return date;
        }

    }
}
#pragma once

#include <string>


//This is Validator class that validates the inputs


class Validator {
public:
    
    static int getValidInt(std::string prompt);

     
    static double getValidDouble(std::string prompt);

     
    static std::string getValidString(std::string prompt);

     
    static std::string getValidDate(std::string prompt);

private:
     
    static bool isValidDate(std::string date);
};
#pragma once
#include <string>

// This class stores one ingredient of a product

class Ingredient {
public:

    // data members
    std::string name;          
    double quantityPerUnit;    

    //  default constructor
    Ingredient();


    // parameterized constructor
    Ingredient(std::string name, double quantityPerUnit);



};




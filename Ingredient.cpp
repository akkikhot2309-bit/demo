#include "Ingredient.h"

// default constructor
Ingredient::Ingredient() {
    name = "";
    quantityPerUnit = 0;
}

// parameterized constructor
Ingredient::Ingredient(std::string name, double quantityPerUnit) {


    //this 
    this->name = name;
    this->quantityPerUnit = quantityPerUnit;

}
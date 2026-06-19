#include "Ingredient.h"

// Default constructor
Ingredient::Ingredient() {
    name = "";
    quantityPerUnit = 0;
}

// Parameterized constructor
Ingredient::Ingredient(std::string name, double quantityPerUnit) {
    this->name = name;
    this->quantityPerUnit = quantityPerUnit;
}
#pragma once
#include <string>

// This class stores one ingredient of a product
// Example: Chemical A needs 2.5 kg per unit of product

class Ingredient {
public:
    std::string name;          // Name of ingredient, e.g. "Chemical A"
    double quantityPerUnit;    // How much is needed per 1 unit of product

    // Default constructor - sets empty values
    Ingredient();

    // Parameterized constructor - set values directly
    Ingredient(std::string name, double quantityPerUnit);
};
#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"

// This class stores full details of one chemical product
// Example: LiquidSoap needs 5L water, 1.5 kWh electricity, 0.3 hr machine time per unit

class Product {
public:
    int id;                              // Unique product ID, e.g. 101
    std::string name;                    // Product name, e.g. "LiquidSoap"
    std::vector<Ingredient> ingredients; // List of all ingredients needed

    double waterPerUnit;                 // Liters of water per unit
    double electricityPerUnit;           // kWh of electricity per unit
    double machineTimePerUnit;           // Hours of machine time per unit

    // Default constructor - sets all values to zero/empty
    Product();
};
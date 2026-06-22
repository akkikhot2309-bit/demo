#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"

// This class is for adding a product and takes help of the Ingredient class 
 
class Product {
public:
    int id;                         //unique id 
    std::string name;                    // product name
    std::vector<Ingredient> ingredients;  // ingrediants needed 

    double waterPerUnit;                 // liters of water per unit
    double electricityPerUnit;           // kWh of electricity per unit
    double machineTimePerUnit;           // hours of machine time per unit

     // constructor to initilize the data
    Product();
};
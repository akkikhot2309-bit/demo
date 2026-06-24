#include "Product.h"

// default constructor 
Product::Product() {
    id = 0;
    name = "";
    waterPerUnit = 0;
    electricityPerUnit = 0;
    machineTimePerUnit = 0;
}


//getters 
int  Product::getId()   const { 
    return id; 
}
std::string   Product::getName()    const { 
    return name; 
}
double   Product::getWaterPerUnit()   const {
    return waterPerUnit;
}
double   Product::getElectricityPerUnit() const {
    return electricityPerUnit;
}
double    Product::getMachineTimePerUnit() const { 
    return machineTimePerUnit; 
}
const std::vector<Ingredient>& Product::getIngredients()       const { 
    return ingredients;
}


// Setters
void Product::setId(int id) { 

    this->id = id;
}

void Product::setName(std::string name) {

    this->name = name;
}

void Product::setWaterPerUnit(double water) { 

    this->waterPerUnit = water; 
}

void Product::setElectricityPerUnit(double elec) { 

    this->electricityPerUnit = elec;
}

void Product::setMachineTimePerUnit(double machine) {

    this->machineTimePerUnit = machine;
}


// Add one ingredient to the list
void Product::addIngredient(const Ingredient& ingredient) {

    ingredients.push_back(ingredient);

}
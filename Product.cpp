#include "Product.h"

// default constructor 
Product::Product() {
    m_id = 0;
    m_name = "";
    m_waterPerUnit = 0;
    m_electricityPerUnit = 0;
    m_machineTimePerUnit = 0;
}


//getters 
int  Product::getId()   const { 
    return m_id; 
}
std::string   Product::getName()    const { 
    return m_name; 
}
double   Product::getWaterPerUnit()   const {
    return m_waterPerUnit;
}
double   Product::getElectricityPerUnit() const {
    return m_electricityPerUnit;
}
double    Product::getMachineTimePerUnit() const { 
    return m_machineTimePerUnit; 
}
const std::vector<Ingredient>& Product::getIngredients()       const { 
    return m_ingredients;
}


// Setters
void Product::setId(int id) { 

    this->m_id = id;
}

void Product::setName(std::string name) {

    this->m_name = name;
}

void Product::setWaterPerUnit(double water) { 

    this->m_waterPerUnit = water; 
}

void Product::setElectricityPerUnit(double elec) { 

    this->m_electricityPerUnit = elec;
}

void Product::setMachineTimePerUnit(double machine) {

    this->m_machineTimePerUnit = machine;
}


// Add one ingredient to the list
void Product::addIngredient(const Ingredient& ingredient) {

    m_ingredients.push_back(ingredient);

}
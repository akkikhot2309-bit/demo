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


// Setters
void Ingredient::setName(std::string name) { 
    
    this->name = name; 

}

void Ingredient::setQuantityPerUnit(double quantity) {

    this->quantityPerUnit = quantity; 

}


//getters
std::string Ingredient::getName() const {

    return name;


}

double  Ingredient::getQuantityPerUnit() const { 

    return quantityPerUnit; 

}




#include "Ingredient.h"

// default constructor
Ingredient::Ingredient() {
    m_name = "";
    m_quantityPerUnit = 0;
}

// parameterized constructor
Ingredient::Ingredient(std::string name, double quantityPerUnit) {


    //this 
    this->m_name = name;
    this->m_quantityPerUnit = quantityPerUnit;

}


// Setters
void Ingredient::setName(std::string name) { 
    
    this->m_name = name; 

}

void Ingredient::setQuantityPerUnit(double quantity) {

    this->m_quantityPerUnit = quantity; 

}


//getters
std::string Ingredient::getName() const {

    return m_name;


}

double  Ingredient::getQuantityPerUnit() const { 

    return m_quantityPerUnit; 

}




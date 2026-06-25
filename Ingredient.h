#pragma once
#include <string>

// This class stores one ingredient of a product

class Ingredient {


private:
    // data members
    std::string m_name;
    double m_quantityPerUnit;


public:

   
   
    //  default constructor
    Ingredient();


    // parameterized constructor
    Ingredient(std::string name, double quantityPerUnit);


    // getters - get the values
    std::string getName()   const;
    double  getQuantityPerUnit() const;


    //setters sets the values
    void setName(std::string name);
    void setQuantityPerUnit(double quantity);

};




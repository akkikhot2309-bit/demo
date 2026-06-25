#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"

// This class is for adding a product and takes help of the Ingredient class 
 
class Product {

private:

    int m_id;                         //unique id 
    std::string m_name;                    // product name
    std::vector<Ingredient> m_ingredients;  // ingrediants needed 

    double m_waterPerUnit;                 // liters of water per unit
    double m_electricityPerUnit;           // kWh of electricity per unit
    double m_machineTimePerUnit;           // hours of machine time per unit


public:

     // constructor to initilize the data
    Product();



    //getters for the products
    int    getId()  const;

    std::string  getName()  const;

    double   getWaterPerUnit()     const;

    double    getElectricityPerUnit() const;

    double   getMachineTimePerUnit() const;

    const std::vector<Ingredient>& getIngredients()   const;




    // setters - for the products
    void setId(int id);

    void setName(std::string name);

    void setWaterPerUnit(double water);

    void setElectricityPerUnit(double electricity);

    void setMachineTimePerUnit(double machineTime);
    


    //for deal with ingrediants 


       // Ingredient list 
    void addIngredient(const Ingredient& ingredient);

    // used during file load
    void setIngredientCount(int count); 



};
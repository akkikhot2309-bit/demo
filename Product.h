#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"

// This class is for adding a product and takes help of the Ingredient class 
 
class Product {

private:

    int id;                         //unique id 
    std::string name;                    // product name
    std::vector<Ingredient> ingredients;  // ingrediants needed 

    double waterPerUnit;                 // liters of water per unit
    double electricityPerUnit;           // kWh of electricity per unit
    double machineTimePerUnit;           // hours of machine time per unit


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
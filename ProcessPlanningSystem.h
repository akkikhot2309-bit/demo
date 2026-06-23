#pragma once
#include <vector>

#include "Product.h"
#include "ProductionSchedule.h"
#include "Validator.h"         




//This is the Main class 
//container that holds all the classes

class ProcessPlanningSystem {
private:
    std::vector<Product> products;               //for storing all products
    std::vector<ProductionSchedule> schedules;  // for storing all the schedules

public:


    // helper that checks for a product in the products array
    Product* findProductById(int id);


    // 8 helper functions 
    


    //  add a new product
    void addProduct();

    // add a new production schedule
    void addProductionSchedule();

    // show forecast report 
    void createForecastReport();

    // show ingredients needed 
    void createIngredientReportByDateRange();

    // save data to files
    void saveData();

    // load data from files
    void loadData();

    // show all products
    void showProducts();

    // show all schedules
    void showSchedules();



};
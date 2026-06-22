#pragma once
#include <string>




// these are for storing the schedules

class ProductionSchedule {
public:
    int productId;    // which product to produce
    std::string date; // yyyy-mm-dd 
    int quantity;     // how many units to produce

    // Default constructor
    ProductionSchedule();
};
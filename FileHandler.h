#pragma once

#include <vector>
#include "Product.h"
#include "ProductionSchedule.h"


// This handles file related activities

class FileHandler {
public:


    // save all products to products.txt
    static bool saveProducts(const std::vector<Product>& products);



    // save all schedules to schedules.txt
    static bool saveSchedules(const std::vector<ProductionSchedule>& schedules);



    // load all products from products.txt
    static bool loadProducts(std::vector<Product>& products);



    // load all schedules from schedules.txt
    static bool loadSchedules(std::vector<ProductionSchedule>& schedules);


};
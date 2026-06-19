#pragma once
#include <vector>
#include "Product.h"
#include "ProductionSchedule.h"

// This is the MAIN class that controls everything
// It holds all products and schedules
// It provides all menu functions

class ProcessPlanningSystem {
private:
    std::vector<Product> products;              // Stores all added products
    std::vector<ProductionSchedule> schedules;  // Stores all production schedules

public:
    // Helper: Find a product by its ID, returns pointer or nullptr if not found
    Product* findProductById(int id);

    // Option 1: Add a new product
    void addProduct();

    // Option 2: Add a new production schedule
    void addProductionSchedule();

    // Option 3: Show forecast report (resource usage for all schedules)
    void createForecastReport();

    // Option 4: Show ingredients needed between two dates
    void createIngredientReportByDateRange();

    // Option 5: Save data to files
    void saveData();

    // Option 6: Load data from files
    void loadData();

    // Extra: Show all products
    void showProducts();

    // Extra: Show all schedules
    void showSchedules();
};
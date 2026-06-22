#include "ProcessPlanningSystem.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

 

//helper find product by id
// return null if product not found

Product* ProcessPlanningSystem::findProductById(int id) {


    for (auto& product : products) {
        if (product.id == id) {
            return &product;
        }
    }
    return nullptr;
}


// add product
void ProcessPlanningSystem::addProduct() {
    Product p;
    int ingredientCount;

    std::cout << "\n";

        
      std::cout << " Add New Product ";

    std::cout << "\n";


    std::cout << "Enter Product ID: ";
     std::cin >> p.id;

    std::cin.ignore();

    // Check if ID already exists
    if (findProductById(p.id) != nullptr) {

        std::cout << "Product ID already exists. Please use a different ID.\n";
        return;

    }

    std::cout << "Enter Product Name: ";
    getline(std::cin, p.name);

    std::cout << "Enter Water required per unit (liters): ";
    std::cin >> p.waterPerUnit;

    std::cout << "Enter Electricity required per unit (kWh): ";
    std::cin >> p.electricityPerUnit;

    std::cout << "Enter Machine Time required per unit (hours): ";
    std::cin >> p.machineTimePerUnit;

    std::cout << "Enter number of ingredients: ";
    std::cin >> ingredientCount;
    std::cin.ignore();

    for (int i = 0; i < ingredientCount; i++) {

        std::string ingName;
        double qty;

        std::cout << "Enter ingredient " << i + 1 << " name: ";
        getline(std::cin, ingName);

        std::cout << "Enter quantity required per unit: ";
        std::cin >> qty;
        std::cin.ignore();

        p.ingredients.push_back(Ingredient(ingName, qty));



    }

    products.push_back(p);
    std::cout << "Product added successfully!\n";



}

// addSchedule
void ProcessPlanningSystem::addProductionSchedule() {
    ProductionSchedule s;

    std::cout << "\n--- Add Production Schedule ---\n";

    std::cout << "Enter Product ID: ";
    std::cin >> s.productId;

    // Check if product exists before adding schedule
    Product* product = findProductById(s.productId);

    if (product == nullptr) {
        std::cout << "Product ID not found. Please add the product first.\n";
        return;
    }

    std::cout << "Enter Production Date (YYYY-MM-DD): ";
    std::cin >> s.date;

    std::cout << "Enter Quantity to produce: ";
    std::cin >> s.quantity;

    schedules.push_back(s);



    std::cout << "Production schedule added successfully!\n";


}

//createForcast
void ProcessPlanningSystem::createForecastReport() {


    if (schedules.empty()) {
       std::cout << "\nNo production schedules available.\n";
        return;
    }

    double totalWater = 0;
    double totalElectricity = 0;
    double totalMachineTime = 0;
    std::cout << " Your Report is here \n";

    std::cout << "\n========== FORECAST REPORT ==========\n";
    std::cout << std::left
        << std::setw(14) << "Date"
        << std::setw(20) << "Product"
        << std::setw(10) << "Qty"
        << std::setw(12) << "Water(L)"
        << std::setw(16) << "Electricity(kWh)"
        << std::setw(16) << "MachTime(hrs)"
        << std::endl;
    std::cout << std::string(88, '-') << std::endl;

    for (const auto& s : schedules) {


        Product* product = findProductById(s.productId);


        //product exists
        if (product != nullptr) {


            double water = product->waterPerUnit * s.quantity;
            double electricity = product->electricityPerUnit * s.quantity;
            double machineTime = product->machineTimePerUnit * s.quantity;



            totalWater += water;
            totalElectricity += electricity;
            totalMachineTime += machineTime;

            std::cout << std::left
                << std::setw(14) << s.date
                << std::setw(20) << product->name
                << std::setw(10) << s.quantity
                << std::setw(12) << water
                << std::setw(16) << electricity
                << std::setw(16) << machineTime
                << std::endl;
        }
    }

    std::cout << std::string(88, '-') << std::endl;
    std::cout << "TOTAL Water Required      : " << totalWater << " L\n";
    std::cout << "TOTAL Electricity Required: " << totalElectricity << " kWh\n";
    std::cout << "TOTAL Machine Time        : " << totalMachineTime << " hrs\n";


    std::cout << "=====================================\n";



}

//createIngrediant
void ProcessPlanningSystem::createIngredientReportByDateRange() {

    if (schedules.empty()) {

        std::cout << "\nNo production schedules available.\n";

        return;

    }

    //take input
    std::string startDate, endDate;

    std::map<std::string, double> ingredientTotals; // ingredient name -> total quantity

    std::cout << "\n--- Ingredients Required Report ---\n";
    std::cout << "Enter Start Date (YYYY-MM-DD): ";
    std::cin >> startDate;
    std::cout << "Enter End Date   (YYYY-MM-DD): ";
    std::cin >> endDate;

    // Loop through all schedules and check if date is within range
    for (const auto& s : schedules) {

        if (s.date >= startDate && s.date <= endDate) {


            Product* product = findProductById(s.productId);


            //found product
            if (product != nullptr) {
                // For each ingredient  product->ingredients , multiply per-unit qty by production quantity

                for (const auto& ing : product->ingredients) {
                    ingredientTotals[ing.name] += ing.quantityPerUnit * s.quantity;
                }
            }


        }
    }

    std::cout << "\n===== INGREDIENTS REQUIRED REPORT =====\n";
    std::cout << "Date Range: " << startDate << " to " << endDate << "\n";
    std::cout << std::string(40, '-') << std::endl;


    //map is not empty
    if (ingredientTotals.empty()) {

        std::cout << "No schedules found in this date range.\n";
        return;

    }

    for (const auto& item : ingredientTotals) {

        std::cout << std::left << std::setw(20) << item.first << ": " << item.second << std::endl;

    }

    std::cout << "========================================\n";


}

// save to files from vectors
void ProcessPlanningSystem::saveData() {


    std::ofstream productFile("products.txt");
    std::ofstream scheduleFile("schedules.txt");


    //error in opening the file
    if (!productFile || !scheduleFile) {
        std::cout << "Error: Could not open file for saving.\n";
        return;
    }

    // Save all products
    //array size products.size()
    productFile << products.size() << std::endl;


    for (const auto& p : products) {
        productFile << p.id << std::endl;
        productFile << p.name << std::endl;
        productFile << p.waterPerUnit << std::endl;
        productFile << p.electricityPerUnit << std::endl;
        productFile << p.machineTimePerUnit << std::endl;
        productFile << p.ingredients.size() << std::endl;

        for (const auto& ing : p.ingredients) {
            productFile << ing.name << std::endl;
            productFile << ing.quantityPerUnit << std::endl;
        }
    }

    // Save all schedules
    scheduleFile << schedules.size() << std::endl;

    for (const auto& s : schedules) {

        scheduleFile << s.productId << std::endl;
        scheduleFile << s.date << std::endl;
        scheduleFile << s.quantity << std::endl;


    }

    std::cout << "Data saved to products.txt and schedules.txt\n";
}

// load to vectors  from file
void ProcessPlanningSystem::loadData() {

    std::ifstream productFile("products.txt");
    std::ifstream scheduleFile("schedules.txt");


    products.clear();
    schedules.clear();

    // Load products
    if (productFile) {

        int productCount;
        productFile >> productCount;
        productFile.ignore();

        for (int i = 0; i < productCount; i++) {

            Product p;
            int ingredientCount;

            productFile >> p.id;
            productFile.ignore();

            std::getline(productFile, p.name);

            productFile >> p.waterPerUnit;
            productFile >> p.electricityPerUnit;
            productFile >> p.machineTimePerUnit;
            productFile >> ingredientCount;

            productFile.ignore();

            for (int j = 0; j < ingredientCount; j++) {
                std::string ingName;
                double qty;

                std::getline(productFile, ingName);

                productFile >> qty;
                productFile.ignore();

                p.ingredients.push_back(Ingredient(ingName, qty));
            }

            products.push_back(p);
        }


        std::cout << "Products loaded from file.\n";
    }


    else {
        std::cout << "No saved product data found.\n";
    }

    // Load schedules
    if (scheduleFile) {


        int scheduleCount;
        scheduleFile >> scheduleCount;
        scheduleFile.ignore();

        for (int i = 0; i < scheduleCount; i++) {
            ProductionSchedule s;

            scheduleFile >> s.productId;
            scheduleFile.ignore();
            std::getline(scheduleFile, s.date);
            scheduleFile >> s.quantity;
            scheduleFile.ignore();

            schedules.push_back(s);

        }


        std::cout << "Schedules loaded from file.\n";
    }


    else {

        std::cout << "No saved schedule data found.\n";

    }


}

// show all products
void ProcessPlanningSystem::showProducts() {

    if (products.empty()) {
        std::cout << "\nNo products added yet.\n";
        return;
    }

    std::cout << "\n========== PRODUCT LIST ==========\n";


    for (const auto& p : products) {


        std::cout << "Product ID    : " << p.id << std::endl;
        std::cout << "Product Name  : " << p.name << std::endl;
        std::cout << "Water/unit    : " << p.waterPerUnit << " L\n";
        std::cout << "Electricity/unit: " << p.electricityPerUnit << " kWh\n";
        std::cout << "Machine Time/unit: " << p.machineTimePerUnit << " hrs\n";
        std::cout << "Ingredients:\n";


        for (const auto& ing : p.ingredients) {


            std::cout << "   - " << ing.name << " : " << ing.quantityPerUnit << " per unit\n";


        }

        std::cout << std::string(34, '-') << std::endl;


    }
}

// show all the schedules
void ProcessPlanningSystem::showSchedules() {


    if (schedules.empty()) {
        std::cout << "\nNo schedules added yet.\n";
        return;


    }

    std::cout << "\n========== PRODUCTION SCHEDULES ==========\n";

    for (const auto& s : schedules) {

        Product* product = findProductById(s.productId);

        std::cout << "Date: " << s.date
            << " | Product ID: " << s.productId
            << " | Product: " << (product ? product->name : "Unknown")
            << " | Quantity: " << s.quantity
            << std::endl;


    }

    std::cout << "==========================================\n";


}
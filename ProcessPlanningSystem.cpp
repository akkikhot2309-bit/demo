#include "ProcessPlanningSystem.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

// -------------------------------------------------------
// HELPER: Find product by ID
// Returns pointer to product if found, nullptr if not found
// -------------------------------------------------------
Product* ProcessPlanningSystem::findProductById(int id) {
    for (auto& product : products) {
        if (product.id == id) {
            return &product;
        }
    }
    return nullptr;
}

// -------------------------------------------------------
// OPTION 1: Add Product
// -------------------------------------------------------
void ProcessPlanningSystem::addProduct() {
    Product p;
    int ingredientCount;

    cout << "\n--- Add New Product ---\n";

    cout << "Enter Product ID: ";
    cin >> p.id;
    cin.ignore();

    // Check if ID already exists
    if (findProductById(p.id) != nullptr) {
        cout << "Product ID already exists. Please use a different ID.\n";
        return;
    }

    cout << "Enter Product Name: ";
    getline(cin, p.name);

    cout << "Enter Water required per unit (liters): ";
    cin >> p.waterPerUnit;

    cout << "Enter Electricity required per unit (kWh): ";
    cin >> p.electricityPerUnit;

    cout << "Enter Machine Time required per unit (hours): ";
    cin >> p.machineTimePerUnit;

    cout << "Enter number of ingredients: ";
    cin >> ingredientCount;
    cin.ignore();

    for (int i = 0; i < ingredientCount; i++) {
        string ingName;
        double qty;

        cout << "Enter ingredient " << i + 1 << " name: ";
        getline(cin, ingName);

        cout << "Enter quantity required per unit: ";
        cin >> qty;
        cin.ignore();

        p.ingredients.push_back(Ingredient(ingName, qty));
    }

    products.push_back(p);
    cout << "Product added successfully!\n";
}

// -------------------------------------------------------
// OPTION 2: Add Production Schedule
// -------------------------------------------------------
void ProcessPlanningSystem::addProductionSchedule() {
    ProductionSchedule s;

    cout << "\n--- Add Production Schedule ---\n";

    cout << "Enter Product ID: ";
    cin >> s.productId;

    // Check if product exists before adding schedule
    Product* product = findProductById(s.productId);
    if (product == nullptr) {
        cout << "Product ID not found. Please add the product first.\n";
        return;
    }

    cout << "Enter Production Date (YYYY-MM-DD): ";
    cin >> s.date;

    cout << "Enter Quantity to produce: ";
    cin >> s.quantity;

    schedules.push_back(s);
    cout << "Production schedule added successfully!\n";
}

// -------------------------------------------------------
// OPTION 3: Forecast Report
// Shows resource usage for all scheduled production
// -------------------------------------------------------
void ProcessPlanningSystem::createForecastReport() {
    if (schedules.empty()) {
        cout << "\nNo production schedules available.\n";
        return;
    }

    double totalWater = 0;
    double totalElectricity = 0;
    double totalMachineTime = 0;

    cout << "\n========== FORECAST REPORT ==========\n";
    cout << left
        << setw(14) << "Date"
        << setw(20) << "Product"
        << setw(10) << "Qty"
        << setw(12) << "Water(L)"
        << setw(16) << "Electricity(kWh)"
        << setw(16) << "MachTime(hrs)"
        << endl;
    cout << string(88, '-') << endl;

    for (const auto& s : schedules) {
        Product* product = findProductById(s.productId);
        if (product != nullptr) {
            double water = product->waterPerUnit * s.quantity;
            double electricity = product->electricityPerUnit * s.quantity;
            double machineTime = product->machineTimePerUnit * s.quantity;

            totalWater += water;
            totalElectricity += electricity;
            totalMachineTime += machineTime;

            cout << left
                << setw(14) << s.date
                << setw(20) << product->name
                << setw(10) << s.quantity
                << setw(12) << water
                << setw(16) << electricity
                << setw(16) << machineTime
                << endl;
        }
    }

    cout << string(88, '-') << endl;
    cout << "TOTAL Water Required      : " << totalWater << " L\n";
    cout << "TOTAL Electricity Required: " << totalElectricity << " kWh\n";
    cout << "TOTAL Machine Time        : " << totalMachineTime << " hrs\n";
    cout << "=====================================\n";
}

// -------------------------------------------------------
// OPTION 4: Ingredients Required Report (by date range)
// -------------------------------------------------------
void ProcessPlanningSystem::createIngredientReportByDateRange() {
    if (schedules.empty()) {
        cout << "\nNo production schedules available.\n";
        return;
    }

    string startDate, endDate;
    map<string, double> ingredientTotals; // ingredient name -> total quantity

    cout << "\n--- Ingredients Required Report ---\n";
    cout << "Enter Start Date (YYYY-MM-DD): ";
    cin >> startDate;
    cout << "Enter End Date   (YYYY-MM-DD): ";
    cin >> endDate;

    // Loop through all schedules and check if date is within range
    for (const auto& s : schedules) {
        if (s.date >= startDate && s.date <= endDate) {
            Product* product = findProductById(s.productId);
            if (product != nullptr) {
                // For each ingredient, multiply per-unit qty by production quantity
                for (const auto& ing : product->ingredients) {
                    ingredientTotals[ing.name] += ing.quantityPerUnit * s.quantity;
                }
            }
        }
    }

    cout << "\n===== INGREDIENTS REQUIRED REPORT =====\n";
    cout << "Date Range: " << startDate << " to " << endDate << "\n";
    cout << string(40, '-') << endl;

    if (ingredientTotals.empty()) {
        cout << "No schedules found in this date range.\n";
        return;
    }

    for (const auto& item : ingredientTotals) {
        cout << left << setw(20) << item.first << ": " << item.second << endl;
    }

    cout << "========================================\n";
}

// -------------------------------------------------------
// OPTION 5: Save Data to Files
// -------------------------------------------------------
void ProcessPlanningSystem::saveData() {
    ofstream productFile("products.txt");
    ofstream scheduleFile("schedules.txt");

    if (!productFile || !scheduleFile) {
        cout << "Error: Could not open file for saving.\n";
        return;
    }

    // Save all products
    productFile << products.size() << endl;
    for (const auto& p : products) {
        productFile << p.id << endl;
        productFile << p.name << endl;
        productFile << p.waterPerUnit << endl;
        productFile << p.electricityPerUnit << endl;
        productFile << p.machineTimePerUnit << endl;
        productFile << p.ingredients.size() << endl;

        for (const auto& ing : p.ingredients) {
            productFile << ing.name << endl;
            productFile << ing.quantityPerUnit << endl;
        }
    }

    // Save all schedules
    scheduleFile << schedules.size() << endl;
    for (const auto& s : schedules) {
        scheduleFile << s.productId << endl;
        scheduleFile << s.date << endl;
        scheduleFile << s.quantity << endl;
    }

    cout << "Data saved to products.txt and schedules.txt\n";
}

// -------------------------------------------------------
// OPTION 6: Load Data from Files
// -------------------------------------------------------
void ProcessPlanningSystem::loadData() {
    ifstream productFile("products.txt");
    ifstream scheduleFile("schedules.txt");

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
            getline(productFile, p.name);
            productFile >> p.waterPerUnit;
            productFile >> p.electricityPerUnit;
            productFile >> p.machineTimePerUnit;
            productFile >> ingredientCount;
            productFile.ignore();

            for (int j = 0; j < ingredientCount; j++) {
                string ingName;
                double qty;

                getline(productFile, ingName);
                productFile >> qty;
                productFile.ignore();

                p.ingredients.push_back(Ingredient(ingName, qty));
            }

            products.push_back(p);
        }
        cout << "Products loaded from file.\n";
    }
    else {
        cout << "No saved product data found.\n";
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
            getline(scheduleFile, s.date);
            scheduleFile >> s.quantity;
            scheduleFile.ignore();

            schedules.push_back(s);
        }
        cout << "Schedules loaded from file.\n";
    }
    else {
        cout << "No saved schedule data found.\n";
    }
}

// -------------------------------------------------------
// EXTRA: Show all products
// -------------------------------------------------------
void ProcessPlanningSystem::showProducts() {
    if (products.empty()) {
        cout << "\nNo products added yet.\n";
        return;
    }

    cout << "\n========== PRODUCT LIST ==========\n";
    for (const auto& p : products) {
        cout << "Product ID    : " << p.id << endl;
        cout << "Product Name  : " << p.name << endl;
        cout << "Water/unit    : " << p.waterPerUnit << " L\n";
        cout << "Electricity/unit: " << p.electricityPerUnit << " kWh\n";
        cout << "Machine Time/unit: " << p.machineTimePerUnit << " hrs\n";
        cout << "Ingredients:\n";
        for (const auto& ing : p.ingredients) {
            cout << "   - " << ing.name << " : " << ing.quantityPerUnit << " per unit\n";
        }
        cout << string(34, '-') << endl;
    }
}

// -------------------------------------------------------
// EXTRA: Show all schedules
// -------------------------------------------------------
void ProcessPlanningSystem::showSchedules() {
    if (schedules.empty()) {
        cout << "\nNo schedules added yet.\n";
        return;
    }

    cout << "\n========== PRODUCTION SCHEDULES ==========\n";
    for (const auto& s : schedules) {
        Product* product = findProductById(s.productId);
        cout << "Date: " << s.date
            << " | Product ID: " << s.productId
            << " | Product: " << (product ? product->name : "Unknown")
            << " | Quantity: " << s.quantity
            << endl;
    }
    cout << "==========================================\n";
}
#include "ProcessPlanningSystem.h"
#include "FileHandler.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

 

//helper find product by id
// return null if product not found

Product* ProcessPlanningSystem::findProductById(int id) {


    for (auto& product : products) {

        if (product.getId() == id) {
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

    // validate ID
    while (true) {

        int id = Validator::getValidInt("Enter Product ID (positive number): ");

        if (id <= 0) {

            std::cout << "  Product ID must be greater than 0.\n";
        }

        else if (findProductById(id) != nullptr) {

           std::cout << "  Product ID " << id << " already exists. Use a different ID.\n";
        }

        else {

            p.setId(id);                  // setter
            break;
        }

    }


    // setter for the products input
     
    p.setName(Validator::getValidString("Enter Product Name: "));     
    

    p.setWaterPerUnit(Validator::getValidDouble("Enter Water per unit (liters): "));     
     

    p.setElectricityPerUnit(Validator::getValidDouble("Enter Electricity per unit (kWh): "));  

    p.setMachineTimePerUnit(Validator::getValidDouble("Enter Machine Time per unit (hrs): "));  



    //take valid inputs
    while (true) {

        ingredientCount = Validator::getValidInt("Enter number of ingredients (at least 1): ");

        if (ingredientCount < 1) {
            std::cout << "  Must have at least 1 ingredient.\n";
        }

        else {
            break;
        }


    }


    //add ingrediants one by one in ingrediants
    for (int i = 0; i < ingredientCount; i++) {

        
        std::cout << "\nIngredient " << i + 1 << ":\n";

        std::string ingName = Validator::getValidString("  Enter ingredient name: ");

        double qty = Validator::getValidDouble("  Enter quantity per unit (> 0): ");


        std::cin.ignore();

        p.addIngredient(Ingredient(ingName, qty));



    }

    products.push_back(p);
    std::cout << "\nProduct \"" << p.getName() << "\" added successfully!\n";

    saveData();






}



// addSchedule production schedules are here
void ProcessPlanningSystem::addProductionSchedule() {


    ProductionSchedule s;

    std::cout << "\n--- Add Production Schedule ---\n";

    //setters
    // valid product id
    while (true) {

        int id = Validator::getValidInt("Enter Product ID: ");

        if (findProductById(id) == nullptr){
            std::cout << "  Product ID " << id << " not found. Add the product first.\n";
        }


        else {
            s.setProductId(id);           // setter
            break;
        }
    }


    // valid date
    s.setDate(Validator::getValidDate("Enter Production Date (YYYY-MM-DD): "));


    // valid quantity
    while (true) {

        int qty = Validator::getValidInt("Enter Quantity to produce: ");

        if (qty <= 0) {

            std::cout << "  Quantity must be greater than 0.\n";
        }

        else {

            s.setQuantity(qty);           // setter
            break;
        }

    }

    schedules.push_back(s);



    std::cout << "Production schedule added successfully!\n";

    saveData();

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

    std::cout << std::string(89, '-') << std::endl;

    for (const auto& s : schedules) {


        Product* product = findProductById(s.getProductId());


        //product exists
        if (product != nullptr) {

            // getters 
            double water = product->getWaterPerUnit() * s.getQuantity();  
            double electricity = product->getElectricityPerUnit() * s.getQuantity();
            double machineTime = product->getMachineTimePerUnit() * s.getQuantity();



            totalWater += water;
            totalElectricity += electricity;
            totalMachineTime += machineTime;

            std::cout << std::left
                << std::setw(14) << s.getDate()
                << std::setw(20) << product->getName()
                << std::setw(10) << s.getQuantity()
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


//createIngrediantReport-> Ingrediants required
void ProcessPlanningSystem::createIngredientReportByDateRange() {

    if (schedules.empty()) {

        std::cout << "\nNo production schedules available.\n";

        return;

    }

    //take input
    std::string startDate, endDate;

    std::map<std::string, double> ingredientTotals; // ingredient name -> total quantity

    std::cout << "\n--- Ingredients Required Report ---\n";

    startDate = Validator::getValidDate("Enter Start Date (YYYY-MM-DD): ");

    endDate = Validator::getValidDate("Enter End Date   (YYYY-MM-DD): ");


    // mistak in date intered
    if (startDate > endDate) {
        std::cout << "  Error: Start date cannot be after end date.\n";
        return;
    }


    // Loop through all schedules and check if date is within range
    for (const auto& s : schedules) {

        if (s.getDate() >= startDate && s.getDate() <= endDate) {


            Product* product = findProductById(s.getProductId());


            //found product
            if (product != nullptr) {

                // For each ingredient  product->ingredients , multiply per-unit qty by production quantity

                for (const auto& ing : product->getIngredients()) {



                    ingredientTotals[ing.getName()] += ing.getQuantityPerUnit() * s.getQuantity();


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

//// save to files from vectors
//void ProcessPlanningSystem::saveData() {
//
//
//    std::ofstream productFile("products.txt");
//    std::ofstream scheduleFile("schedules.txt");
//
//
//    //error in opening the file
//    if (!productFile || !scheduleFile) {
//        std::cout << "Error: Could not open file for saving.\n";
//        return;
//    }
//
//    // Save all products
//    //array size products.size()
//    productFile << products.size() << std::endl;
//
//
//    for (const auto& p : products) {
//        productFile << p.id << std::endl;
//        productFile << p.name << std::endl;
//        productFile << p.waterPerUnit << std::endl;
//        productFile << p.electricityPerUnit << std::endl;
//        productFile << p.machineTimePerUnit << std::endl;
//        productFile << p.ingredients.size() << std::endl;
//
//        for (const auto& ing : p.ingredients) {
//            productFile << ing.name << std::endl;
//            productFile << ing.quantityPerUnit << std::endl;
//        }
//    }
//
//    // Save all schedules
//    scheduleFile << schedules.size() << std::endl;
//
//    for (const auto& s : schedules) {
//
//        scheduleFile << s.productId << std::endl;
//        scheduleFile << s.date << std::endl;
//        scheduleFile << s.quantity << std::endl;
//
//
//    }
//
//    std::cout << "Data saved to products.txt and schedules.txt\n";
//}
//
//// load to vectors  from file
//void ProcessPlanningSystem::loadData() {
//
//    std::ifstream productFile("products.txt");
//    std::ifstream scheduleFile("schedules.txt");
//
//
//    products.clear();
//    schedules.clear();
//
//    // Load products
//    if (productFile) {
//
//        int productCount;
//        productFile >> productCount;
//        productFile.ignore();
//
//        for (int i = 0; i < productCount; i++) {
//
//            Product p;
//            int ingredientCount;
//
//            productFile >> p.id;
//            productFile.ignore();
//
//            std::getline(productFile, p.name);
//
//            productFile >> p.waterPerUnit;
//            productFile >> p.electricityPerUnit;
//            productFile >> p.machineTimePerUnit;
//            productFile >> ingredientCount;
//
//            productFile.ignore();
//
//            for (int j = 0; j < ingredientCount; j++) {
//                std::string ingName;
//                double qty;
//
//                std::getline(productFile, ingName);
//
//                productFile >> qty;
//                productFile.ignore();
//
//                p.ingredients.push_back(Ingredient(ingName, qty));
//            }
//
//            products.push_back(p);
//        }
//
//
//        std::cout << "Products loaded from file.\n";
//    }
//
//
//    else {
//        std::cout << "No saved product data found.\n";
//    }
//
//    // Load schedules
//    if (scheduleFile) {
//
//
//        int scheduleCount;
//        scheduleFile >> scheduleCount;
//        scheduleFile.ignore();
//
//        for (int i = 0; i < scheduleCount; i++) {
//            ProductionSchedule s;
//
//            scheduleFile >> s.productId;
//            scheduleFile.ignore();
//            std::getline(scheduleFile, s.date);
//            scheduleFile >> s.quantity;
//            scheduleFile.ignore();
//
//            schedules.push_back(s);
//
//        }
//
//
//        std::cout << "Schedules loaded from file.\n";
//    }
//
//
//    else {
//
//        std::cout << "No saved schedule data found.\n";
//
//    }
//
//
//}


// save to files from storage
void ProcessPlanningSystem::saveData() {

    bool productsSaved = FileHandler::saveProducts(products);
    bool schedulesSaved = FileHandler::saveSchedules(schedules);

    if (productsSaved && schedulesSaved) {
        std::cout << "Data saved to products.txt and schedules.txt\n";
    }
}

//load from files to storage
void ProcessPlanningSystem::loadData() {
    products.clear();
    schedules.clear();

    FileHandler::loadProducts(products);
    FileHandler::loadSchedules(schedules);
}


// show all products
void ProcessPlanningSystem::showProducts() {

    if (products.empty()) {
        std::cout << "\nNo products added yet.\n";
        return;
    }

    std::cout << "\n========== PRODUCT LIST ==========\n";


    for (const auto& p : products) {


        std::cout << "Product ID    : " << p.getId() << std::endl;
        std::cout << "Product Name  : " << p.getName() << std::endl;
        std::cout << "Water/unit    : " << p.getWaterPerUnit() << " L\n";
        std::cout << "Electricity/unit: " << p.getElectricityPerUnit() << " kWh\n";
        std::cout << "Machine Time/unit: " << p.getMachineTimePerUnit() << " hrs\n";
        std::cout << "Ingredients:\n";


        for (const auto& ing : p.getIngredients() ) {


            std::cout << "   - " << ing.getName() << " : " << ing.getQuantityPerUnit() << " per unit\n";


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

        Product* product = findProductById(s.getProductId());

        std::cout << "Date: " << s.getDate()
            << " | Product ID: " << s.getProductId()
            << " | Product: " << (product ? product->getName() : "Unknown")
            << " | Quantity: " << s.getQuantity()
            << std::endl;


    }

    std::cout << "==========================================\n";


}
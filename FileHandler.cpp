#include "FileHandler.h"
#include <iostream>
#include <fstream>


// products to products.txt
bool FileHandler::saveProducts(const std::vector<Product>& products) {



    std::ofstream productFile("products.txt");
   


    //error in opening the file
    if (!productFile) {
        std::cout << "Error: Could not open file for saving.\n";
        return false;
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


    return true;


}



//save shedules to schedules.txt
bool FileHandler::saveSchedules(const std::vector<ProductionSchedule>& schedules) {


    std::ofstream scheduleFile("schedules.txt");





        if(!scheduleFile) {
            std::cout << "Error: Could not open schedules.txt for saving.\n";
            return false;
        }


    // Save all schedules
    scheduleFile << schedules.size() << std::endl;

    for (const auto& s : schedules) {

        scheduleFile << s.productId << std::endl;
        scheduleFile << s.date << std::endl;
        scheduleFile << s.quantity << std::endl;


    }

    return true;


 }


// products to products.txt
bool FileHandler::loadProducts(std::vector<Product>& products) {


    std::ifstream productFile("products.txt");

    if (!productFile) {
        std::cout << "No saved product data found. Starting fresh.\n";
        return false;
    }


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



    return true;

}






bool FileHandler::loadSchedules(std::vector<ProductionSchedule>& schedules) {


    std::ifstream scheduleFile("schedules.txt");


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

    return true;



}


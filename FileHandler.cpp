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


        productFile << p.getId() << std::endl;
        productFile << p.getName() << std::endl;
        productFile << p.getWaterPerUnit() << std::endl;
        productFile << p.getElectricityPerUnit() << std::endl;
        productFile << p.getMachineTimePerUnit() << std::endl;
        productFile << p.getIngredients().size() << std::endl;

        for (const auto& ing : p.getIngredients() ) {
            productFile << ing.getName() << std::endl;
            productFile << ing.getQuantityPerUnit() << std::endl;
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

        scheduleFile << s.getProductId() << std::endl;
        scheduleFile << s.getDate() << std::endl;
        scheduleFile << s.getQuantity() << std::endl;


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
            int id, ingredientCount;
            std::string name;
            double water, electricity, machineTime;

            productFile >> id;
            productFile.ignore();
            getline(productFile, name);
            productFile >> water >> electricity >> machineTime;
            productFile >> ingredientCount;
            productFile.ignore();


            p.setId(id);                          // setter
            p.setName(name);                      // setter
            p.setWaterPerUnit(water);             // setter
            p.setElectricityPerUnit(electricity); // setter
            p.setMachineTimePerUnit(machineTime); // setter

            for (int j = 0; j < ingredientCount; j++) {


                std::string ingName;
                double qty;

                std::getline(productFile, ingName);

                productFile >> qty;
                productFile.ignore();

                p.addIngredient(Ingredient(ingName, qty));


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


            //copy from txt
            int productId, quantity;
            std::string date;

            scheduleFile >> productId;
            scheduleFile.ignore();

            getline(scheduleFile, date);
            scheduleFile >> quantity;
            scheduleFile.ignore();



            //set here
            s.setProductId(productId);   
            s.setDate(date);            
            s.setQuantity(quantity);     

            schedules.push_back(s);

        }


        std::cout << "Schedules loaded from file.\n";
    }


    else {

        std::cout << "No saved schedule data found.\n";

    }

    return true;



}


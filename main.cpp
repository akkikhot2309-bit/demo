#include <iostream>
#include "ProcessPlanningSystem.h"



int main() {
    ProcessPlanningSystem system;
    int choice=-1;


    // Auto-load saved data when program starts
    std::cout << "Loading saved data...\n";
    system.loadData();



    do {

            std::cout << "\n====================================\n";

            std::cout << "   PROCESS PLANNING SYSTEM\n";
            std::cout << "   Chemical Plant Management\n";

            std::cout << "\n\n\n";



            std::cout << "1. Add Product\n";
            std::cout << "2. Add Production Schedule\n";
            std::cout << "3. Create Forecast Report\n";
            std::cout << "4. Create Ingredients Required Report\n";
            std::cout << "5. Save Data\n";
            std::cout << "6. Load Data\n";
            std::cout << "7. Show All Products\n";
            std::cout << "8. Show All Schedules\n";
            std::cout << "0. Exit\n";
            std::cout << "------------------------------------\n";
             

            // Keep asking until valid number is entered
            do {

                std::cout << "Enter your choice: ";
                std::cin >> choice;

                if (std::cin.fail()) {

                    std::cin.clear();

                   std:: cin.ignore();
                   std:: cout << "Invalid input. Please enter a number between 0 and 8.\n";

                }

                else if (choice < 0 || choice > 8) {
                    std::cout << "Invalid choice. Please enter a number between 0 and 8.\n";
                }

                else {
                    break;  
                }



            } while (true);

 
 




        switch (choice) {
        case 1:
            system.addProduct();
            break;
        case 2:
            system.addProductionSchedule();
            break;
        case 3:
            system.createForecastReport();
            break;
        case 4:
            system.createIngredientReportByDateRange();
            break;
        case 5:
            system.saveData();
            break;
        case 6:
            system.loadData();
            break;
        case 7:
            system.showProducts();
            break;
        case 8:
            system.showSchedules();
            break;
        case 0:
            // Auto-save before exit
            system.saveData();
            std::cout << "Data saved. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter 0-8.\n";
        }

    } while (choice != 0);

    return 0;
}
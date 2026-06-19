#include <iostream>
#include "ProcessPlanningSystem.h"

using namespace std;

int main() {
    ProcessPlanningSystem system;
    int choice;


    // Auto-load saved data when program starts
    cout << "Loading saved data...\n";
    system.loadData();

    do {
        cout << "\n====================================\n";
        cout << "   PROCESS PLANNING SYSTEM\n";
        cout << "   Chemical Plant Management\n";
        cout << "====================================\n";
        cout << "1. Add Product\n";
        cout << "2. Add Production Schedule\n";
        cout << "3. Create Forecast Report\n";
        cout << "4. Create Ingredients Required Report\n";
        cout << "5. Save Data\n";
        cout << "6. Load Data\n";
        cout << "7. Show All Products\n";
        cout << "8. Show All Schedules\n";
        cout << "0. Exit\n";
        cout << "------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

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
            cout << "Data saved. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please enter 0-8.\n";
        }

    } while (choice != 0);

    return 0;
}
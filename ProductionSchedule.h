#pragma once
#include <string>

// This class stores one production schedule entry
// Example: On 2026-06-20, produce 100 units of Product ID 101

class ProductionSchedule {
public:
    int productId;    // Which product to manufacture
    std::string date; // Date in YYYY-MM-DD format, e.g. "2026-06-20"
    int quantity;     // How many units to produce

    // Default constructor
    ProductionSchedule();
};
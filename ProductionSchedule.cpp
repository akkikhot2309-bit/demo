#include "ProductionSchedule.h"

// default constructor 
ProductionSchedule::ProductionSchedule() {
    productId = 0;
    date = "";
    quantity = 0;
}

// getters
int   ProductionSchedule::getProductId() const {

    return productId; 
}
std::string ProductionSchedule::getDate()  const { 

    return date; 
}
int     ProductionSchedule::getQuantity()  const { 

    return quantity;
}

// setters
void ProductionSchedule::setProductId(int id) {

    this->productId = id; 
}
void ProductionSchedule::setDate(std::string date) { 

    this->date = date;
}
void ProductionSchedule::setQuantity(int quantity) { 

    this->quantity = quantity;
}







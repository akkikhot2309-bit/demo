#include "ProductionSchedule.h"

// default constructor 
ProductionSchedule::ProductionSchedule() {
    m_productId = 0;
    m_date = "";
    m_quantity = 0;
}

// getters
int   ProductionSchedule::getProductId() const {

    return m_productId; 
}
std::string ProductionSchedule::getDate()  const { 

    return m_date; 
}
int     ProductionSchedule::getQuantity()  const { 

    return m_quantity;
}

// setters
void ProductionSchedule::setProductId(int id) {

    this->m_productId = id; 
}
void ProductionSchedule::setDate(std::string date) { 

    this->m_date = date;
}
void ProductionSchedule::setQuantity(int quantity) { 

    this->m_quantity = quantity;
}







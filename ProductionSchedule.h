#pragma once
#include <string>




// these are for storing the schedules

class ProductionSchedule {
private:
    int productId;    // which product to produce
    std::string date; // yyyy-mm-dd 
    int quantity;     // how many units to produce


public:

    // Default constructor
    ProductionSchedule();

    // getters 
    int   getProductId() const;

    std::string getDate()  const;

    int  getQuantity()  const;


    // setters   
    void setProductId(int productId);
    void setDate(std::string date);
    void setQuantity(int quantity);


};
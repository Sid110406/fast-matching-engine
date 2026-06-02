#pragma once

#include<string> 

enum class OrderType{
    LIMIT, 
    MARKET
}; 

enum class Side{
    BUY, 
    SELL
}; 

class Order{
public: 
    Order(uint64_t order_id, std::string symbol, Side side, OrderType order, int price, int quantity); 

    // achiving encapsulation : 
    uint64_t get_order_id() const; 
    const std::string& get_symbol() const;  // a reference to the string in order to avoid the copying ; 
    Side get_side() const; 
    int get_price() const; 
    OrderType get_type() const; 
    int get_original_quantity() const; 
    int get_remaining_quantity() const; 

    void reduce_quantity(int amount); // to reduce the quantity by the amount 
    bool is_filled() const; 

private :
    uint64_t order_id; 
    std::string symbol; 
    Side side; 
    OrderType type; 
    int price; 
    int original_quantity; 
    int remaining_quantity; 
}; 

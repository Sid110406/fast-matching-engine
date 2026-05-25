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
    Order(unsigned long long order_id, std::string symbol, Side side, OrderType order, int price, int quantity, unsigned long long sequence_number); 

    // achiving encapsulation : 
    unsigned long long get_order_id() const; 
    const std::string& get_symbol() const;  // a reference to the string in order to avoid the copying ; 
    Side get_side() const; 
    int get_price() const; 
    OrderType get_type() const; 
    int get_original_quantity() const; 
    int get_remaining_quantity() const; 
    unsigned long long get_sequence_number() const; 

    void reduce_quantity(int amount); // to reduce the quantity by the amount 
    bool is_filled() const; 

private :
    unsigned long long order_id; 
    std::string symbol; 
    Side side; 
    OrderType type; 
    int price; 
    int original_quantity; 
    int remaining_quantity; 
    unsigned long long sequence_number; 
}; 

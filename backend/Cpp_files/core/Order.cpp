#include "Order.h"

Order::Order(unsigned long long order_id, std::string symbol, Side side, OrderType type, int price, int quantity, unsigned long long sequence_number){
    this->order_id = order_id; 
    this->symbol = symbol; 
    this->side = side; 
    this->type = type; 
    this->price = price; 
    this->original_quantity = quantity; 
    this->remaining_quantity = quantity; 
    this->sequence_number = sequence_number; 
}

//accessor
unsigned long long Order::get_order_id() const{
    return this->order_id; 
}

const std::string& Order::get_symbol() const{
    return this->symbol; 
}

Side Order::get_side() const{
    return this->side; 
}

OrderType Order::get_type() const {
    return this->type;
}

int Order::get_price() const {
    return this->price;
}

int Order::get_original_quantity() const {
    return this->original_quantity;
}

int Order::get_remaining_quantity() const {
    return this->remaining_quantity;
}

unsigned long long Order::get_sequence_number() const {
    return this->sequence_number;
}

// functions : 

void Order::reduce_quantity(int amount) {
    if(amount <= 0){ // edgeCase; 
        return ; 
    }
    if(amount > this->remaining_quantity){
        amount = this->remaining_quantity; 
    }
    this->remaining_quantity -= amount; 
}

bool Order::is_filled() const {
    return this->remaining_quantity == 0;
}

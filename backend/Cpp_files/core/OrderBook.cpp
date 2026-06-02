#include "OrderBook.h"
#include<iterator>
#include<algorithm>
#include<cassert>

OrderBook::OrderBook(const std::string& symbol){
    this->symbol = symbol; 
    this->next_trade_sequence = 1; 
}; 
std::vector<Trade> OrderBook::add_limit_order(Order& order){ // this function also returns all the trades that happened; 
    std::lock_guard<std::mutex> lock(mtx); 

    std::vector<Trade> trades; 
    if(order.get_side() == Side::BUY){
        trades = match_buy_order(order); 
        if(!order.is_filled()){
            buy_book[order.get_price()].emplace_back(order); 
            order_index[order.get_order_id()] = {true, order.get_price(), std::prev(buy_book[order.get_price()].end())}; 
        }
    }
    else{
        trades = match_sell_order(order); 
        if(!order.is_filled()){
            sell_book[order.get_price()].emplace_back(order); 
            order_index[order.get_order_id()] = {false, order.get_price(), std::prev(sell_book[order.get_price()].end())}; 

        }
    }
    return trades; 
}
std::vector<Trade> OrderBook::process_market_order(Order& order){ // returns the trade that happened by adding this order; 
    std::lock_guard<std::mutex> lock(mtx); 

    if(order.get_side() == Side::BUY){
        return match_buy_order(order); 
    }
    else{
        return match_sell_order(order); 
    }
}  
std::vector<Trade> OrderBook::match_buy_order(Order& order){
    std::vector<Trade> trades; 
    while(!order.is_filled() && !sell_book.empty()){
        auto best_sell = sell_book.begin();  // itterator of the map to get the queue of the lowest price; 
        int price = best_sell->first;  // the lowest sell price available; 
        if(order.get_type() == OrderType::LIMIT && price > order.get_price()){
            break; 
        }
        auto& queue = best_sell->second;
        Order& sell_order = queue.front(); 
        int trade_quant = std::min(sell_order.get_remaining_quantity(), order.get_remaining_quantity()); 
        // for checking out if any error happens; 
            assert(trade_quant > 0); 
            assert(price > 0); 
            assert(order.get_order_id() != sell_order.get_order_id());

        trades.emplace_back(Trade{order.get_order_id(), sell_order.get_order_id(), price, trade_quant, next_trade_sequence++}); 
        sell_order.reduce_quantity(trade_quant); 
        order.reduce_quantity(trade_quant); 
        if(sell_order.is_filled()){
            order_index.erase(sell_order.get_order_id()); // removing this also from the list made for cancellation of order as it just got completed
            queue.pop_front(); 
        }
        if(queue.empty()){
            sell_book.erase(best_sell);
        }
    } 
    return trades;  
}
std::vector<Trade> OrderBook::match_sell_order(Order& order){
    std::vector<Trade> trades; 
    while(!order.is_filled() && !buy_book.empty()){
        auto best_buy = buy_book.begin(); 
        int price = best_buy->first; 
        if(order.get_type() == OrderType::LIMIT && price < order.get_price()){
            break; 
        }
        auto& queue = best_buy->second; 
        auto& buy_order = queue.front();
        int trade_quant = std::min(order.get_remaining_quantity(), buy_order.get_remaining_quantity());
        
        // for checking out if any error happens; 
            assert(trade_quant > 0); 
            assert(price > 0); 
            assert(order.get_order_id() != buy_order.get_order_id());
        
        trades.emplace_back(Trade{buy_order.get_order_id(), order.get_order_id(), price, trade_quant, next_trade_sequence++}); 
        buy_order.reduce_quantity(trade_quant); 
        order.reduce_quantity(trade_quant); 
        if(buy_order.is_filled()){
            order_index.erase(buy_order.get_order_id());  // location of this order id is no more required for the cancellation; 
            queue.pop_front(); 
        }
        if(queue.empty()){
            buy_book.erase(best_buy); // remove this from the map entirely; 
        }
    }
    return trades; 
}

int OrderBook::best_buy_price() const {
    std::lock_guard<std::mutex> lock(mtx); 

    if (buy_book.empty()) {
        return -1;
    }
    return buy_book.begin()->first;
}

int OrderBook::best_sell_price() const {
    std::lock_guard<std::mutex> lock(mtx); 

    if (sell_book.empty()) {
        return -1;
    }
    return sell_book.begin()->first;
}

bool OrderBook::cancel_order(uint64_t order_id) {
    std::lock_guard<std::mutex> lock(mtx);

    if(order_index.find(order_id) == order_index.end()){
        return false; // unable to delete as the order does not even exsist; 
    }
    auto it = order_index.find(order_id); 
    OrderLocation loc = (it)->second;
    if(loc.is_buy){
        buy_book[loc.price].erase(loc.it); // remove this from the queue; 
        if(buy_book[loc.price].empty()){ 
            buy_book.erase(loc.price); 
        }
    } 
    else{
        sell_book[loc.price].erase(loc.it); 
        if(sell_book[loc.price].empty()){
            sell_book.erase(loc.price); 
        }
    }
    order_index.erase(it);  // also delete from the order_index as the order is cancelled and no longer exsists; 
    return true; 
}
const std::string& OrderBook::get_symbol() const{
    return this->symbol; 
}
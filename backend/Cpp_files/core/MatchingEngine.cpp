#include "MatchingEngine.h"

OrderBook& MatchingEngine::get_or_create_book(const std::string& symbol){ 
    {
        std::shared_lock<std::shared_mutex> read_lock(map_rw_mutex); 
        auto it = books.find(symbol); 
        if(it != books.end()){
            return *(it->second); 
        }
    }
    return create_book(symbol); 
}

OrderBook& MatchingEngine::create_book(const std::string& symbol){
    // acquire the lock

    std::unique_lock<std::shared_mutex> write_lock(map_rw_mutex); 
    auto it = books.find(symbol); 
    if(it == books.end()){
        // now create; 
        auto result = books.emplace(symbol, std::make_unique<OrderBook>(symbol)); 
        it = result.first; 
    }
    return *(it->second); 
}

std::vector<Trade> MatchingEngine::submit_limit_order(Order& order){
    return (get_or_create_book(order.get_symbol())).add_limit_order(order); 
}

std::vector<Trade> MatchingEngine::submit_market_order(Order& order){
    return (get_or_create_book(order.get_symbol())).process_market_order(order);
}

bool MatchingEngine::cancel_order(const std::string& symbol, uint64_t order_id){
    std::shared_lock<std::shared_mutex> read_lock(map_rw_mutex);
    auto it = books.find(symbol); 
    if(it == books.end()){
        return false; 
    }
    return (it->second)->cancel_order(order_id); 
}

int MatchingEngine::best_buy_price(const std::string& symbol) const{
    std::shared_lock<std::shared_mutex> read_lock(map_rw_mutex); 
    auto it = books.find(symbol); 
    if(it == books.end()){
        return -1; // no OrderBook for this symbol;  
    }
    return (it->second)->best_buy_price(); 
}   

int MatchingEngine::best_sell_price(const std::string& symbol) const{
    std::shared_lock<std::shared_mutex> read_lock(map_rw_mutex); 
    auto it = books.find(symbol); 
    if(it == books.end()){
        return -1; // no OrderBook for this symbol;  
    }
    return (it->second)->best_sell_price(); 
}

bool MatchingEngine::book_exists(const std::string& symbol) const{
    std::shared_lock<std::shared_mutex> read_lock(map_rw_mutex); 
    auto it = books.find(symbol); 
    if(it == books.end()){
        return false; 
    }
    return true; 
}
#pragma once
#include <unordered_map>
#include <string>
#include<shared_mutex> 
#include<memory> 
#include "Order.h"
#include "OrderBook.h"

class MatchingEngine{
public: 
    MatchingEngine() = default; 
    std::vector<Trade> submit_limit_order(Order& order); 
    std::vector<Trade> submit_market_order(Order& order); 
    bool cancel_order(const std::string& symbol, uint64_t order_id); 
    int best_buy_price(const std::string& symbol) const; 
    int best_sell_price(const std::string& symbol) const;
    bool book_exists(const std::string& symbol) const; 

    std::vector<std::string> get_symbols() const; 

    private: 
    std::unordered_map<std::string, std::unique_ptr<OrderBook>> books; // contains the orderBook of each of the symbol   
    // problem -- what if 2 threads simulatenously call this get_or_create_book() for the same symbol 2 same books will get created twice race_condition; 

    // will fix this by another mutex for the books; 
    // issue -- the problem of rehashing can destroy the reference, 
    // using the reader writter problem to fix this problem of the rehashing, the reader will be given priority ! 

    mutable std::shared_mutex map_rw_mutex; 
    OrderBook& get_or_create_book(const std::string& symbol);  // creates the book if it does not exsits; and returns the orderBook of a particular symbol 
    OrderBook& create_book(const std::string& symbol);
}; 
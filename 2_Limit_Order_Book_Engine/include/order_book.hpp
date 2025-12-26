#pragma once
#include "order.hpp"
#include <map>
#include <unordered_map>

struct PriceLevel{
    Price price;
    Qty   total_qty = 0;
    Order* head     = nullptr;   //oldest order
    Order* tail     = nullptr;   //newest order
};

class OrderBook{
    public:
        void add_order(Order* order);
        void cancel_order(OrderID id);

        Price best_bid() const;
        Price best_ask() const;

        void print_book() const;
    
    private:
        std::map<Price, PriceLevel, std::greater<Price>> bids; //highest price first
        std::map<Price, PriceLevel> asks;
        std::unordered_map<OrderID, Order*> order_map;

        void add_to_level(PriceLevel& level, Order* order);
        void remove_from_level(PriceLevel& level, Order* order);
};
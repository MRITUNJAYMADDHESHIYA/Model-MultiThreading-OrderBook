#include "order_book.hpp"
#include <iostream>

//fifo + o(1) insertion/deletion + quantity tracking
void OrderBook::add_to_level(PriceLevel& level, Order* order){

    //new order added at the tail
    order->prev = level.tail; //prev points to old tail
    order->next = nullptr;    //next is null as it's the newest order

    if(level.tail){
        level.tail->next = order;
    }else{
        level.head = order;
    }

    level.tail = order;
    level.total_qty += order->qty;
}

void OrderBook::remove_from_level(PriceLevel& level, Order* order){
    if(order->prev){
        order->prev->next = order->next;
    }else{
        level.head = order->next;
    }

    if(order->next){
        order->next->prev = order->prev;
    }else{
        level.tail = order->prev;
    }

    level.total_qty -= order->qty;
}

void OrderBook::add_order(Order* order){
    auto& book = (order->side == Side::Buy) ? bids : asks;
    auto& level = book[order->price];

    level.price = order->price;
    add_to_level(level, order);
    order_lookup[order->id] = order;
}

void OrderBook::cancel_order(OrderID id){
    auto it = order_lookup.find(id);
    if(it == order_lookup.end()) return;

    Order* order = it->second;
    auto& book = (order->side == Side::Buy) ? bids : asks;

    auto level_it = book.find(order->price);
    if(level_it == book.end()) return;

    remove_from_level(level_it->second, order);
    if(level_it->second.total_qty == 0){
        book.erase(level_it);
    }

    order_lookup.erase(it);
}

Price OrderBook::best_bid() const{
    if(bids.empty()) return 0;
    return bids.begin()->first;
}

Price OrderBook::best_ask() const{
    if(asks.empty()) return 0;
    return asks.begin()->first;
}

void OrderBook::print_book() const{
    std::cout<< "\n---ORDER BOOK---\n";

    std::cout<< "Asks:\n";
    for(auto& [p, level_it] : asks){
        std::cout<< "Price: " << p << " Total Qty: " << level_it.total_qty << "\n";
    }

    std::cout<< "Bids:\n";
    for(auto& [p, level_it] : bids){
        std::cout<< "Price: " << p << " Total Qty: " << level_it.total_qty << "\n";
    }
}

#include "matching_engine.hpp"
#include <iostream>

void MatchingEngine::process(Order* order){
    if(order->side == Side::Buy){
        match_buy(order);
    }else{
        match_sell(order);
    }
}

void MatchingEngine::match_buy(Order* order){
    while(order->qty > 0 && book.best_ask() && book.best_ask() <= order->price){
        Price ask_price = book.best_ask();
        book.cancel_order(0);
        break;
    }

    if(order->qty > 0){
        book.add_order(order);
    }
}

void MatchingEngine::match_sell(Order* order){
    while(order->qty > 0 && book.best_bid() && book.best_bid() >= order->price){
        Price bid_price = book.best_bid();
        book.cancel_order(0);
        break;
    }

    if(order->qty > 0){
        book.add_order(order);
    }
}

void MatchingEngine::trade(OrderID taker, OrderID maker, Qty qty, Price price){
    std::cout << "Trade executed: Taker " << taker << ", Maker " << maker
              << ", Qty " << qty << ", Price " << price << std::endl;   
}
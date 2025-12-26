#include "order_book.hpp"
#include<iostream>

int main(){
    OrderBook book;
    Order o1{1, Side::Buy, 100, 10};
    Order o2{2, Side::Sell, 105, 5};
    Order o3{3, Side::Buy, 101, 15};

    book.add_order(&o1);
    book.add_order(&o2);
    book.add_order(&o3);

    book.print_book();
}


#include "orderbook.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

int Order::order_count_bid = 0;
int Order::order_count_ask = 0;

void OrderBook::flipBalance(const std::string& userId1, const std::string& userId2, double quantity, double price) {
    // Implement the logic to flip balances between two users
    // This function should update the balances of userId1 and userId2 based on the quantity and price of the matched order

    if(users.find(userId1) != users.end() && users.find(userId2) != users.end()) {
        if(users[userId1].user_balance.balance["USD"] >= price * quantity){
            if(users[userId2].user_balance.balance[ticker] >= quantity){
                users[userId1].user_balance.balance["USD"] -= price * quantity;
                users[userId2].user_balance.balance["USD"] += price * quantity;

                users[userId1].user_balance.balance[ticker] += quantity;
                users[userId2].user_balance.balance[ticker] -= quantity;

                cout << "Funds and stocks transfered! " << endl;
            } else {
                cout << "User does not have enough balance to sell the stock " << endl;
            }
        }else{
            cout<<"User does not have enough balance to buy the stock " << endl;
        }
    }else{
        cout<<"One or both users do not exist in the system." << endl;
    }
}


std::string OrderBook::makeUser(std::string Username){
    User user(Username); //create a user with default balance
    users[Username] = user; //add user to the users map
    cout<<"User:" <<Username<<"created successfully "<<endl;
    return "User created successfully";
}


std::string OrderBook::add_bid(std::string Username, int Price, int Quantity){
    
}
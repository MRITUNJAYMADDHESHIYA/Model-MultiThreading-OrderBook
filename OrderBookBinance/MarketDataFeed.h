#pragma once

#include<variant> //it's like auto
#include<string>
#include<chrono>
#include "Types.h"
#include "OrderType.h"

//market data message
enum class MessageType{
    NewOrder,
    CancelOrder,
    ModifyOrder,
    Trade,        //trade executed
    BookSnapshoot //full book 
};

//for new order
struct NewOrderMessage{
    MessageType type = MessageType::NewOrder;
    OrderId     orderId;
    Side        side;
    Price       price;
    Quantity    quantity;
    OrderType   orderType;
    std::chrono::system_clock::time_point timestamp;
};

//for order cancellation
struct CancelOrderMessage{
    MessageType type = MessageType::CancelOrder;
    OrderId     OrderId;
    std::chrono::system_clock::time_point timestamp;
};

//for order modification
struct ModifyOrderMessage{
    MessageType type
}
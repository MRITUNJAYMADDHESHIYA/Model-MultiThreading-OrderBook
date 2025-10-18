#pragma once

#include<memory>
#include<list>
#include<format>
#include<stdexcept>
#include "Types.h"
#include "OrderType.h"
#include "Order.h"
#include "Constants.h"

class Order{
    public:
        Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
            :orderType_{orderType},
             orderId_{orderid},
             side_{side},
             price_{price},
             initialQuantity_{quantity},
             remainingQuantity_{quantity}{
                 if(quantity == 0){
                     throw std::invalid_argument("Order quantity must be greater than zero");
                 }
             }
        
        //delegating constructor(avoid duplicate code)
        Order(OrderId orderId, Side side, Quantity quantity)
            :Order(OrderType::Market, orderId, side, Constants::InvalidPrice, quantity){}

        OrderId   GetOrderId()           const {return orderId_;}
        Side      GetSide()              const {return side_;}
        Price     GetPrice()             const {return price_;}
        OrderType GetOrderType()         const {return orderType_;}
        Quantity  GetInitialQuantity()   const {return initialQuantity_;}
        Quantity  GetRemainingQuantity() const {return remainigQuantity_;}
        Quantity  GetFillQuantity()      const {return GetInitialQuantity() - GetRemainingQuantity();}
        bool      IsFilled()             const {return GetRemainingQuantity() == 0;}

        void Fill(Quantity quantity){
            if(quantity > GetRemainingQuantity()){
                throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));
            }
            remainingQuantity_ -= quantity;
        }

        void ToGoodTillCancel(Price price){
            if(orderType_ != OrderType::Market){
                throw std::logic_error("Cannot convert non-market order to GoodTillCancel");
            }

            price_ = price;
            orderType_ = OrderType::GoodTillCancel;
        }

    private:
        OrderType orderType_;
        OrderId   orderId_;
        Side      side_;
        Price     price_;
        Quantity  initialQuantity_;
        Quantity  GetRemainingQuantity_;
};


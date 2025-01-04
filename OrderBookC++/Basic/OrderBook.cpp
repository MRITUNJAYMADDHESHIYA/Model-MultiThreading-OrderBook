#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>

class OrderBook{
    public:
        enum class OrderType {Market, Limit, GoodTillCanceled, FillOrKill_Limit};
        enum class Side {Buy, Sell};

        class Order{
            public:
                //constructor
                Order(int id, OrderType type, Side side, double price, int quantity): id(id), type(type), side(side), price(price), quantity(quantity){}

                //attributes
                int getId() const{return id;}
                OrderType getTyoe() const {return type;}
                Side getSide() const {return side;}
                double getPrice() const{return price;}
                int getQuantity() const{return quantity;}

                //update order quantity
                void setQuantity(int new_quantity) {quantity = new_quantity;}

            private:
                int id;
                OrderType type;
                Side side;
                int quantity;
        };



        //add an order to the order book
        void addOrder(const Order& order){
            orders.push_back(order);
        }

        //cancel an order by its ID
        void cancelOrder(int orderId){
            auto it = std::remove_if(orders.begin(), orders.end(), [orderId](const Order& order){
                return order.getId() == orderId;
            });

            if(it != orders.end()){
                std::cout<<"Canceled Order ID: "<<orderId<< std::endl;
                orders.erase(it, orders.end());
            }
        }

        //match order in the order book

    private:
        std::vector<Order> orders; //store orders in the order book

        //findMatch will help to find a match for a given order
        std::vector<Order>::iterator findMatch(std::vector<Order>::iterator orderIt, int quantity, bool fulMatch = false){
            for(auto it=orders.begin(); it != orders.end(); it++){
                if(it->getSide() != orderIt->getSide() &&
                   ((orderIt->getSide() == Side::Buy && it->getPrice() <= orderIt->getPrice()) || 
                    (orderIt->getSide() == Side::Sell && it->getPrice() >= orderIt->getPrice())) &&
                    (!fulMatch || it->getQuantity() >= quantity)){ //remaining quantity get filled 
                    reutrn it;
                }
            }
            return orders.end();
        }

        //Execute an order
        void executeOrder(std::vector<Order>::iterator& orderIt, std::vector<Order>::iterator& matchIt){
            double fillPrice = matchIt->getPrice();
            std::cout<<"Matched Order ID: " <<orderIt->getId() << "with Order ID:" <<matchIt->getId()<<"at price: "<<std::fixed << std::setprecision(2)<< fillPrice << "quantity: "<< orderIt->getQuantity() << std::endl;
            matchIt->setQuantity(matchIt->getQuantity() - orderIt->getQuantity());

            if(matchIt->getQuantity() == 0){
                orders.erase(matchIt);
            }
        }

        //print individual order
        void printOrder(const Order& order) const{
            std::cout<<"Order ID:"<<order.getId()
                     <<", Type: "<<static_cast<int>(order.getType())
                     <<", Side: "<<(order.getSide() == Side::Buy ? "Buy": "Sell")
                     <<", Price: "<<order.getPrice()
                     <<", Quantity: "<<order.getQuantity()<<std::endl;
        }
};

int main(){
    OrderBook orderBook;

    OrderBook::Order order1(1, OrderBook::OrderType::Market, OrderBook::Side::Buy, 0, 10);
    OrderBook::Order order2(2, OrderBook::OrderType::Limit, OrderBook::Side::Sell, 101.0, 20);
    OrderBook::Order order3(3, OrderBook::OrderType::Limit, OrderBook::Side::Sell, 99.0, 5);
    OrderBook::Order order4(4, OrderBook::OrderType::Market, OrderBook::Side::Buy, 0, 15);
    OrderBook::Order order5(5, OrderBook::OrderType::GoodTillCanceled, OrderBook::Side::Buy, 102.0, 10);
    OrderBook::Order order6(6, OrderBook::OrderType::FillOrKill_Limit, OrderBook::Side::Sell, 100.0, 8);
    OrderBook::Order order7(7, OrderBook::OrderType::FillOrKill_Limit, OrderBook::Side::Sell, 99.0, 12);
    OrderBook::Order order8(8, OrderBook::OrderType::FillOrKill_Limit, OrderBook::Side::Buy, 101.0, 8);
    
}
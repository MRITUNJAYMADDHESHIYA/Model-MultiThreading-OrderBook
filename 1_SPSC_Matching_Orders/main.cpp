//Basic order insertion + matching and a simple SPSC(Single Producer, Single Consumer) ring buffer for passing messages between threads
#include<bits/stdc++.h>
#include<thread>
#include<atomic>

//1.push and pop operations are lock-free and wait-free
//2.uses atomic operations to ensure thread safety without traditional locking mechanisms
//////////////////////////////SPSC Ring Buffer///////////////////////////////////////
template<typename T>
class SPSCQueue{
    std::vector<T> buffer;
    const size_t   capacity;
    std::atomic<size_t> head{0}, tail{0};

    public:
        SPSCQueue(size_t cap): capacity(cap), buffer(cap) {} //constructor
        bool push(const T& item){
            size_t t = tail.load(std::memory_order_relaxed);
            size_t h = head.load(std::memory_order_acquire);

            if ((t + 1) % Capacity == h){
                return false; // full
            }
            buffer[t % Capacity] = item;
            tail.store(t + 1, std::memory_order_release);
            return true;
        }

        bool pop(T &out){
            size_t h = head.load(std::memory_order_relaxed);
            size_t t = tail.load(std::memory_order_acquire);

            if (h == t){
                return std::nullopt; // empty
            }
            out = buffer[h];
            head.store((h + 1)% capacity, std::memory_order_release);
            return true;
        }
};

/////////////////////////////Order and PriceLevel///////////////////////////////////////
using Price = int64_t; //I can change it to double if needed
struct Order{
    uint64_t id;       //unique order id
    bool     isBuy;    //true for buy, false for sell
    Price    price;    //price per unit
    uint64_t quantity; //quantity of units
    Order(uint64_t i, bool b, Price p, uint64_t q): id(i), isBuy(b), price(p), quantity(q) {}
};

struct PriceLevel{
    Price             price;
    std::deque<Order> orders;
};

///////////////////////////////// Books /////////////////////////////////////////
class OrderBook{
    //map for price sorting
    std::map<Price, PriceLevel, std::greater<Price>> bids; //descending for bids
    std::map<Price, PriceLevel, std::less<Price>>    asks; //ascending for asks

    //adding limit order and try to match
    std::vector<std::tuple<uint64_t, uint64_t, Price, uint64_t>> addOrder(Order Basket){
        std::vector<std::tuple<uint64_t, uint64_t, Price, uint64_t>> trades; //maker_id, taker_id, price, qty

        if(Basket.isBuy){
            while(Basket.quantity && !asks.empty()){
                auto it = asks.begin();
                if(it->first > Basket.price) break; //no match

                auto &pl = it->second;
                while(Basket.quantity && !pl.orders.empty()){
                    Order maker   = pl.orders.front();
                    uint64_t fill = std::min(maker.quantity, Basket.quantity);
                    trades.emplace_back(maker.id, Basket.id, maker.price, fill);
                    Basket.quantity -= fill;
                    maker.quantity -= fill;

                    if(maker.quantity == 0){
                        pl.orders.pop_front();
                    } else {
                        pl.orders.front().quantity = maker.quantity;
                    }
                }
                if(pl.orders.empty()){
                    asks.erase(it);
                }
            }
            if(Basket.quantity > 0){
                bids[Basket.price].price = Basket.price;
                bids[Basket.price].orders.push_back(Basket);
            }
        }else{
            while(Basket.quantity && !bids.empty()){
                auto it = bids.begin();
                if(it->first < Basket.price) break; //no match

                auto &pl = it->second;
                while(Basket.quantity && !pl.orders.empty()){
                    Order maker   = pl.orders.front();
                    uint64_t fill = std::min(maker.quantity, Basket.quantity);
                    trades.emplace_back(maker.id, Basket.id, maker.price, fill);
                    Basket.quantity -= fill;
                    maker.quantity -= fill;

                    if(maker.quantity == 0){
                        pl.orders.pop_front();
                    } else {
                        pl.orders.front().quantity = maker.quantity;
                    }
                }
                if(pl.orders.empty()){
                    bids.erase(it);
                }
            }
            if(Basket.quantity > 0){
                asks[Basket.price].price = Basket.price;
                asks[Basket.price].orders.push_back(Basket);
            }
        }
        return trades;
    }
};


///////////////////////////////// Main /////////////////////////////////////////
int main(){
    SPSCQueue<std::shared_ptr<Order>> st(1024); //capacity of 1024
    OrderBook ob;

    //producer thread
    //push orders to the queue
    std::thread producer([&](){
        uint64_t id = 1;

        //resting bids
        st.push(std::make_shared<Order>(id++, true, 100, 10)); //buy 10 @ 100
        st.push(std::make_shared<Order>(id++, true, 101, 15));

        //resting asks
        st.push(std::make_shared<Order>(id++, false, 105, 10)); //sell 10 @ 105
        st.push(std::make_shared<Order>(id++, false, 104, 20));

        //aggressive taker buy => matches asks
        st.push(std::make_shared<Order>(id++, true, 106, 25)); //buy 25 @ 106
        //aggressive taker sell => matches bids
        st.push(std::make_shared<Order>(id++, false, 99, 20));
    });
}
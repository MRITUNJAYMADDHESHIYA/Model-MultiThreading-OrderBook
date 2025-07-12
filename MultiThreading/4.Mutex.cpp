#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

//Mutex: Mutual Exclusion  
//mutex is used to avoid the race condition
//we use lock(), unlock() on mutex to avoid  race condition

//Race condition:->
//1.racc condition is a situation where two or more tread happend to change a common data at the same time.

int myAmount = 0;
std::mutex m;

void addMoney(){
    m.lock();
    ++myAmount;
    m.unlock();
}


int main(){
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    t1.join();
    t2.join();

    cout<<myAmount<<endl;
    return 0;
}

//////mutex::try_lock()
//1.Try to lock the mutex.return immediately
//2.

int counter=0;
std::mutex mtx;

void increaseTheCounter(){
    for(int i=0; i<100000; i++){
        if(mtx.try_lock()){
            ++counter;
            mtx.unlock();
        }
    }
}

int main(){
    std::thread t1(increaseTheCounter);
    std::thread t2(increaseTheCounter);

    t1.join();
    t2.join();

    cout<< "counter" <<counter<<endl;
    return 0;
}


///std::try_lock() in c++
///it can try to lock multiple mutex objects at the same time
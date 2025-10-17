#include<iostream>

class Demo{
    public:
        int x;
        void show(){
            std::cout << this->x << std::endl;
        }
};
int main(){
    Demo d1{10};
    d1.show();
}
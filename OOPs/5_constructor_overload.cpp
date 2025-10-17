#include<iostream>
using namespace std;

class Point{
    public:
        Point(){cout<<"Default\n";}
        Point(int x){cout<<"One Parameter\n";}
        Point(int x, int y){cout<<"Two Parameter\n";}
};

Point p1;
Point p2(5);
Point p3(3, 5);
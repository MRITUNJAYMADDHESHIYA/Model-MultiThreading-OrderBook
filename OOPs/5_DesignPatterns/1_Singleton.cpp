//1.The Singleton pattern ensures that a class has only one instance and provides a global point of access to that instance.
//

#include<iostream>

class Singleton{
    private:
        static Singleton* instance;
        Singleton(){} //
}
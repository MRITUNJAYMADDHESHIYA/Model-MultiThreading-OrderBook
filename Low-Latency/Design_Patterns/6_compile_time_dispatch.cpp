//1.The decision of which function or code path to call is made at compile time, not at runtime.
//Remove virtual function overhead
//Removes branches and dynamic checks
//Enables inlining

//use:- templates, constexpr



#include<benchmark_test>/benchmark.h>

class Base{
    public:
        virtual ~Base() {}
        virtual int function() const = 0;
};

class Derived1 : public Base{
    public:
        int function() const override{
            return 1;
        }
};

class Derived2 : public Base{
    public:
        int function() const override{
            return 2;
        }
};

//////////Runtime dispatch
static void BM_RuntimeDispatch(benchmark::State& state){
    
    
}






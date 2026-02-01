#include "FuncPtrTest.h"
#include <iostream>

using namespace  std;

void printHello()
{
    cout << "hello"<<endl;
};
int square(int num)
{
    return num*num;
};
double addDouble(double a, double b)
{
    return a+b;
};

using printHelloPtr= void(*)();
using squarePtr= int(*)(int);
using addDoublePtr= double(*)(double, double);

typedef void(*printHelloPtr2)();
typedef int(*squarePtr2)(int);
typedef double(*addDoublePtr2)(double, double);

#define outputTest ptr1();\
cout << ptr2(6)<<endl; \
cout << ptr3(6.6,3.9)<<endl
class Output
{
public:
    Output(string input):outputstr(input)
    {
        print(outputstr+"begin");
    };

    ~Output()
    {
        print(outputstr+"end");
    }

    
private:
    string outputstr;
    void print(const string& msg)
    {
        cout << "------------------------" << msg <<"----------------------" <<endl;
    }
};

int subtract(int a, int b)
{
    return a-b;
}
int multiply(int a, int b)
{
    return a*b;
}
int add(int a, int b)
{
    return a+b;
}


int calculator(int a, int b, int (*op)(int, int))
{
    return op(a,b);
}
using SimPtr =int(*)(int,int);
using CalPtr =int(*)(int, int, int(*)(int,int));

void callbackPrint(int result)
{
    cout << "result" << result <<endl;
}
typedef int(*OpFunc)(int,int);
using CallbackFunc=void(*)(int);

void advancedCalculator(int a, int b, OpFunc op, CallbackFunc cb)
{
    int result  = op(a,b);
    cb(result);
}

void FuncPtrTest::Test()
{
    {
        Output s("using");
        printHelloPtr ptr1= &printHello;        
        squarePtr ptr2= &square;        
        addDoublePtr ptr3= &addDouble;
        outputTest;
        
    }
    {
        Output s("typedef");
        printHelloPtr2 ptr1 = &printHello;
        squarePtr2 ptr2 = &square;
        addDoublePtr2 ptr3 = &addDouble;
        outputTest;
    }
    {
        Output s("normal");
        void(*ptr1)() = &printHello;
        int(*ptr2)(int) = &square;
        double(*ptr3)(double, double) = &addDouble;
        outputTest;
    }

    {
        Output s("second");
        SimPtr subPtr = &subtract;
        SimPtr mulPtr = &multiply;
        CalPtr calPtr = &calculator;
        cout << calPtr(5, 3, subPtr)<<endl;
        cout << calPtr(5, 3, mulPtr)<<endl;
    }
    {
        Output s("array");
        // int p[4];
        int(*addPtr)(int,int) = &add;

        int(*p1[3])(int, int) = {&subtract, &multiply, &add};
        SimPtr p[3] = {&subtract, &multiply, &add};
        for(int i = 0; i < 3; i++)
        {
            cout << (p[i])(3,5) << endl;
        }
        for(int i = 0; i < 3; i++)
        {
            cout << (p1[i])(3,5) << endl;
        }
    }

    {
        advancedCalculator(3, 15, &multiply, &callbackPrint);
    }
}

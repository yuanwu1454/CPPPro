#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{

    int b = 3;
    auto ptf = [&b](int a)
    {
        printf("a = %d\n", a+b);
        b = 4;
    };

    ptf(3);
    printf("b = %d\n", b);
    return 0;
}

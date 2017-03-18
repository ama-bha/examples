#include <iostream>
#include "typelist.h"
#include "virtualtest.h"

int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}

int multiply (int x, int y)
{
   return x * y;
}

// the compiler may evaluate this at compile tim


int maintest_templates(int argc, char *argv[])
{
    int x[factorial(5)];
    int t =34;
    int y=455+t;
    std::cout << "length of floating types" << TLength<floating_point_types>::value;
    std::cout << "index of double in floating types" << TContains<double,floating_point_types>::value;
    std::cout <<  "1st value in floating types is " << type2string<  TTypeAT<floating_point_types,0>::resulttype >::value;
    std::cout <<  "test char[] template " << y << typestring<'H','e','l','l','o'>::data();
    return 0;
}

int main()
{
    VirtualTest* B = new VirtualTest();
    B->nonvirt();

    VirtualTest* D = new VirtualTestD();
    D->nonvirt();

    VirtualTestD* E = new VirtualTestD();
    E->nonvirt();

    std::cout << "------------------------" << std::endl;
    VirtualTestD* F = static_cast<VirtualTestD*>(new VirtualTest());
    E->nonvirt();
    std::cout << F->z << std::endl;

    return 0;
}



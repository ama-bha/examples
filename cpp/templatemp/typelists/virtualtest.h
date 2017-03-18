#ifndef VIRTUALTEST_H
#define VIRTUALTEST_H

#include <iostream>

class VirtualTest
{
public:
    VirtualTest();

    void nonvirt() {
        std::cout << "Nonvirt function in Base class" << std::endl;
        virt();
    }
    virtual void virt() {
        std::cout << "virt function in Base class" << std::endl ;
    }

};

class  VirtualTestD : public VirtualTest {
public:
    int z;
    void nonvirt() {
        std::cout << "Nonvirt function in derived class" << std::endl;
        z=34;
        std::cout << z << std::endl;
        virt();
    }
    virtual void virt() {
        std::cout << "virt function in derived class" << std::endl ;
    }

};

#endif // VIRTUALTEST_H

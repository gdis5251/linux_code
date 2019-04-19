#include <iostream>
#include <stdio.h>

class Base
{
public:
    virtual void Fun1 ()
    {
        std::cout << "Base::Fun1" << std::endl;
    }

    virtual void Fun2 ()
    {
        std::cout << "Base::Fun2" << std::endl;
    }

    void Fun3 ()
    {
        std::cout << "Base::Fun3" << std::endl;
    }

protected:
    int _b;
};

class Derive : public Base
{
public:
    virtual void Fun1 () override
    {
        std::cout << "Derive::Fun1" << std::endl;
    }

protected:
    int _d;
};


int main(void)
{
    Base b;
    Derive d;

    printf("addr: %p\n", *(int*)&b);
    printf("addr: %p\n", &Base::Fun1);
    printf("addr: %p\n", &Base::Fun3);

    return 0;
}

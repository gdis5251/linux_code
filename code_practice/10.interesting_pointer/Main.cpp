#include <iostream>

struct S
{
    int a;
    int *p;
};

int main(void)
{
    struct S s;
    int *p = &s.a;

    p[0] = 1;
    p[1] = 2;

    s.p = p;
    s.p[1] = 1;
    s.p[0] = 2;

    std::cout << "a : " << s.a << "  p : " << s.p << std::endl;
    return 0;
}

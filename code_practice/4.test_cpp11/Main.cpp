#include <list>
#include <iostream>

void TestList1()
{
    std::list<int> l1;
    l1.push_front(4);
    l1.push_front(3);
    l1.push_front(2);
    l1.push_front(1);
    l1.push_front(0);

    for (const auto& e : l1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main(void)
{
    TestList1();

    return 0;
}
